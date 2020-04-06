/******************************************************************************
 *
 * Copyright (c) 2019 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer.
 *  
 * 2. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *  Detector3.h
 *
 *****************************************************************************/

// 2019/05/24
// This class is mainly based on C APIs of detector.c and image.c in C:/darknet-master/src
// Note:
// 1. We have changed the class name list in list,h to ylist to avoid ambiguity between this list  and std::list.
// 2. We have also changed the class name data in darknet,h to ydatat to avoid ambiguity between this data  and std::data.

// 2019/06/16 Modified detect_image method to take the thhree parameters.

#pragma once
#define USE_STD

#define IMPORT
#define OPENCV

#include <vector>
#include <sol/opencv/OpenCVObject.h>
#include <darknet_ext.h>
#include <list.h>

#include <box.h>          //do_nms_sort
#include <data.h>         //get_labels_custom
#include <image.h>        //load_alphabet, load_image
#include <image_opencv.h> //load_image
#include <region_layer.h>
#include <cost_layer.h>
#include <utils.h>

#include <network.h>      //fuse_conv_batchnorm, calculate_binary_weights, network_predict, get_network_boxes
#include <option_list.h>  //read_data_cfg
#include <parser.h>       //load_weight, parse_network_cfg_custom

#include <fstream>
#include <iostream>

namespace SOL {

class Detector3 {

private:
  float thresh        = 0.24;
  float hier_thresh   = 0.5;
  ylist*    options   = nullptr;
  
  char*     name_list = nullptr;
  char**    names     = nullptr;
  std::vector<std::string> names_vector;
  
  image**   alphabet  = nullptr;
  network   net; 

public:
  //Convert method from image to cv::Mat. 
  cv::Mat image_to_mat(image img)
  {
    int channels = img.c;
    int width = img.w;
    int height = img.h;
    cv::Mat mat = cv::Mat(height, width, CV_8UC(channels));
    int step = mat.step;

    for (int y = 0; y < img.h; ++y) {
      for (int x = 0; x < img.w; ++x) {
        for (int c = 0; c < img.c; ++c) {
          float val = img.data[c*img.h*img.w + y*img.w + x];
          mat.data[y*step + x*img.c + c] = (unsigned char)(val * 255);
        }
      }
    }
    return mat;
  }


  std::vector<std::string> read_object_names(const std::string&  filename, int& names_size) 
  {
    std::ifstream file(filename);
    std::vector<std::string> names;
    if (!file.is_open()) {
      return names;
    } 
    char line[256]; 
    int size = 0;
    while (file.getline(line, sizeof(line)-1)) {
      //printf("%d %s\n", size++, line);
      names.push_back(std::string(line) );
      size++;
    }
    names_size = size;
    std::cout << "object names loaded \n";
    return names;
  }


  void **list_to_array(std::vector<std::string>& list)
  {
    void** array = (void**)calloc(list.size(), sizeof(void*));
    int count = 0;
    for (int i = 0; i< list.size(); i++) {
      
      array[i] = (char*)list[i].c_str();
      printf("%s\n", array[i]);
    }
    return array;
  }


  image **load_alphabet_image(const char* path="C:/darknet-master")
  {
    const int nsize = 8;
    image** alphabets = (image**)calloc(nsize, sizeof(image*));
    printf("load_alphabet_image\n");
    for(int j = 0; j < nsize; ++j){
        alphabets[j] = (image*)calloc(128+1, sizeof(image));
        for(int i = 32; i < 127; ++i){
          char buff[256];
          sprintf(buff, "%s/data/labels/%d_%d.png", path, i, j);
          //printf("fullath:%s\n", buff);
          alphabets[j][i] = load_image_color(buff, 0, 0);
        }
    }
    return alphabets;
  }

  
public:
  //
  // Constructor
  Detector3(const std::string darknet_root,  //"C:/darknet-master"
            const std::string& cfgfile, 
            const std::string& weightfile, 
            const std::string& cocofile,
            float thresh=0.24,
            float hier_thresh=0.5)
  :thresh(thresh),
  hier_thresh(hier_thresh)
  {
    options   = read_data_cfg((char*)cfgfile.c_str());

    int names_size = 0;
    names_vector   = read_object_names(cocofile, names_size); //coco_names; 
    names          = (char**)list_to_array(names_vector); 

    alphabet = load_alphabet_image((char*)darknet_root.c_str());
    
    net = parse_network_cfg_custom((char*)cfgfile.c_str(), 1, 1); // set batch=1

    load_weights(&net, (char*)weightfile.c_str());

    fuse_conv_batchnorm(net);
    calculate_binary_weights(net);
    if (net.layers[net.n - 1].classes != names_size) {
      printf(" Error: in the file %s number of names %d that isn't equal to classes=%d in the file %s \n",
          name_list, names_size, net.layers[net.n - 1].classes, cfgfile);
      if (net.layers[net.n - 1].classes > names_size) {
        getchar();
      }
    }
    srand(2222222);
    
  }

  //
  // Destructor
  ~Detector3()
  {
    // free memory
    // 2019/06/16 
    //free_ptrs((void**)names, net.layers[net.n - 1].classes);
    free((void**)names); //Modified to Detector3 class.

    free_list_contents_kvp(options);
    free_list(options);

    const int nsize = 8;
    for (int j = 0; j < nsize; ++j) {
        for (int i = 32; i < 127; ++i) {
            ::free_image(alphabet[j][i]);
        }
        free(alphabet[j]);
    }
    free(alphabet);

    free_network(net);
  }

  //See detector.c file in C:/darknet-master/src
  //Return an image that bounding rectangles of detected objects and labels are drawn in an image corresponding to a filename.  
  //A csv ile of csv_filename is created, which includes detailed information on the detected objects.
  //2019/06/16 Modified to take three parameters.
  image detect_image(const char* filename, const char* save_image_filename, const char* csv_filename)
  {
    int j;
    float nms = .45;    // 0.4F

    image im      = load_image((char*)filename, 0, 0, net.c);
    
    image sized   = resize_image(im, net.w, net.h);
    int letterbox = 0;
    //image sized = letterbox_image(im, net.w, net.h); letterbox = 1;
    layer l = net.layers[net.n - 1];

    float *X = sized.data;

    //time= what_time_is_it_now();
    //double time = get_time_point();
    network_predict(net, X);
 
    //printf("%s: Predicted in %lf milli-seconds.\n", filename, ((double)get_time_point() - time) / 1000);

    int nboxes = 0;
    detection *dets = get_network_boxes(&net, im.w, im.h, thresh, hier_thresh, 0, 1, &nboxes, letterbox);

    if (nms) {
      do_nms_sort(dets, nboxes, l.classes, nms);
    }
    int show_id_only = 1;
    draw_detections_v3_ext(im, dets, nboxes, thresh, names, alphabet, l.classes, csv_filename, show_id_only);
    
    //2019/06/16
    printf("Save filename [%s]\n", save_image_filename);
    save_image(im, save_image_filename);  //saved as a name of  save_image_filename + ".jpg"
    //  save_image(im, "predictions");

    free_detections(dets, nboxes);

    free_image(sized);
    return im;
  }
      
};


}

