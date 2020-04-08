<html>
<!--
<head>
<meta name="viewport" content="width=device-width, initial-scale=1.0">

<meta http-equiv="Content-Type" content="text/html; charset=iso8859-1">
<meta name="description"
        content="OpenCV, OpenGL, DirectX, Direct3D10, Direct3D11, Direct3D12, SolApplets, SolFileCypher. SolMailProxy. Antillia.com. SolFileFinder. SOL9 (SOL++2000 Updated) Class Library for Windows. Free C++ class library for Windows are available.">

<meta name="keywords"
        content="OpenCV, OpenGL, DirectX;Direct3D10;Direct3D11;Direct3D12;SolApplets;SolFileCypher;SolMailProxy;Antillia.com;SolFileFinder;Java; SOL9; SOL9 C++ Class Library;SOL++2000; SOL++2000 Class Library; Windows Class Library; C++ Class Library; Object Oriented Programming;C++">
<meta name="Author" content="Tom Atlan">
<meta http-equiv="Pragma:" content="no-cache">
<meta http-equiv="Cache-Control" content="no-cache">
-->
<style type="text/css">
body {
    color: #00; background: #FFF;
    margin-left:0; 
    margin-right:0;
    margin-top:0;
    margin-bottom:0;
   font-family: arial,verdana,helvetica,tahoma,sans-serif; 
}
a:link { color: "#003344"}
a:hover {color:"red"}
a:visited { color: #72f; background:#fff}    

td.left a:link { color: "#003344"}
td.left a:hover {color:"red"}
td.left a:visited { color: #003344 ; background: #ddeeff}

td {
  word-wrap:break-word;
}

pre {
  white-space: -moz-pre-wrap;
  white-space: -pre-wrap;
  white-space: -o-pre-wrap;
  white-space: pre-wrap;
  word-wrap: break-word;
}
</style>

<!--
#00eecc }
 -->
 <!--
<title>
Antillia.com
</title>

<script type="text/javascript">
function confirmation(message, url) {
  if(window.confirm(message)){
    location.href = url + ".zip"; 
  } else{
      //window.alert('Canceled');
  }
}

</script>
-->
</head>

<body bgcolor="white" topmargin="0" leftmargin="0">
<table border="0" width="100%" cellspacing="0" cellpadding="3">
<tr>
<td bgcolor="#003344" align="middle" background='.http://www.antillia.com/sol9.2.0/images/solarsystem.jpg' >

<font size=6 color ="white" >

&nbsp;&nbsp;Welcome to Software Laboratory of Antillia.com.<br>
&nbsp;&nbsp;&nbsp;&nbsp;Future Windows and Linux Programming<br>

</font>
</td>

</tr>
</table>


<!-- Right Begin -->
<!--
================================================================================================
-->

<br clear="all">

 
<TABLE CELLSPACING="0" CELLPADDING="2" BORDER="0" WIDTH="100%">
<TR>
<TD COLSPAN="3" HEIGHT="20" VALIGN="MIDDLE" BGCOLOR="#003399">

<!--
<TD COLSPAN="3" HEIGHT="20" VALIGN="MIDDLE" BGCOLOR="darkgreen">
-->
<FONT size="5" 
COLOR="#ffffff" SIZE="-1">&nbsp;&nbsp;SOL9 C++ Class Library 2.1
</FONT></TD>
</TR></TABLE>
<!--
-->
<div style="margin : 4px 4px 4px 4px">

<br>
<!-- Top anchors begin -->

<table border="0"  cellspacing="4"><tr>
<td class="left">
&nbsp;
<a href="http://www.antillia.com/sol9.2.0/samples.html">
<font size = 2 color="navy">
<b>SOL9 Samples</b>
</font>
</a>
&nbsp;
</td>

<td class="left">
&nbsp;
<a href="http://www.antillia.com/sol9.2.0/tutorial.html">
<font size = 2  color="navy">
<b>SOL9 Tutorial</b>
</font>
</a>
&nbsp;
</td>

<td class="left">
&nbsp;
<a href="http://www.antillia.com/sol9.2.0/faq.html">
<font size = 2  color="navy">
<b>SOL9 FAQ</b>
</font>
</a>
&nbsp;
</td>


<td  class ="left">
&nbsp;

<a href="http://www.antillia.com/sol9.2.0/classtree.html">

<b>
<font size = 2 color="navy">
SOL9 ClassTree
</font>
</b>
</a>
&nbsp;

</td>
<td class="left">
&nbsp;

<a href="http://www.antillia.com/sol9.2.0/classlist.html">

<b>
<font size = "2" color="navy">
SOL9 ClassList
</font>
</b>
</a>
&nbsp;

</td>
</tr>
</table>
<!-- Top anchors end -->

<!--
<font size = 2 color="red">
<b>
<li>25 Mar 2001:Added chapter 5.
</b>
</font>
-->
<font size = 3 color="black">
<hr noshade color ="gray">

<b>

1 What is SOL9? <br>
</b>
</font>

<font size=2>
<b>1.1 SOL9</b>
<br>

SOL9 is one of the simplest C++ class libraries for Windows10. It is based on author's previous version SOL++2000. 
We provide a set of C++ class header files and a lot of sample programs.<br>
</font>

<b>
<font size=2>
One of the striking features of SOL9 is the simplicity of handling of Windows events.<br> 
</b>
Historically, the author started to develop the original SOL++ C++ library on Windows 95 about twenty years ago. 
And now here is a new version of SOL9 for  Visual Studio 2019 on Windows 10.<br>
The SOL9 library is based on the previous SOL++2000. For original SOL++ library, see author's book(<font color = "green"><b>Windows95 Super class library,
SOFTBANK Japan:ISBN4-7973-0018-3).</b></font>
<br>
 The hierarchy of SOL9 is quite similar to that of SOL++2000.
 But We have introduced a namespace 'SOL' to avoid collision of some class names 
 in Windows API. But the basic implementation of SOL9 is same with old SOL++2000.<br>
 On SOL9 we implemented all the member functions inside the C++ classes; of cource, you may not like it.
 This is not a conventional coding style of C++ of separating implementation and interface. 
 Since we are not faithful followers of a conventional C++ coding style, we don't care about a policy of the separationism of interfarce and implementation.

 But SOL9 coding style has one point which enables a rapid prototyping of writing and testing C++ prograqms quickly. 
 It may (or may not) be useful for various experimentation projects. <br>
 
</p>

<!--
<font size=2>
 Our design policy of the SOL9 is to provide simple and unified C++ classes to develop GUI applications, which 
 are based on a model of callbacks and event handlers.

<br>
<br>
 -->
 </font>
 <font size=2 >
 The latest SO9 library supports not only traditional Windows applications, but also Direct3D10, Direct3D11, Direct3D12, OpenGL and OpenCV
applications, which are our main ROI these days. For details, please refer our <a href="http://www.antillia.com/sol9.2.0/samples.html">samples page</a>. 
<br>
</font>

<br>
<b>
<font size=2>
1.2 Download SOL9 Library<br>
</b>
</font>
<b>
<br>
SOL9-2.1 C++ Class Library for Windows 10 (Library & Samples)
<br>
<a href="http://www.antillia.com/sol9.2.0/sol9-2.1.5-vs2019-win10-version-1903.zip">Download sol9-2.1.5-vs2019-win10-version-1903</a>
</b>
<br>
<br>
<font size=2>
A set of SOL9 C++ Class Library and sample programs for Windows is available. This is a free C++ class library for all Windows programmers.
<br>
The latest version supports the standard Windows APIs, Direct3D10, Direct3D11, Direct3D12, OpenGL and OpenCV-4.2.0 on Window 10 Version 1903, and
we have updated SOL::SmartPtr class to use std::unique_ptr of C++11.
Furthermore, to support OpenCV--4.2.0, we have updated <a href="http://www.antillia.com/sol9.2.0/classes/OpenCVImage.html">OpenCVImage</a>, 
<a href="http://www.antillia.com/sol9.2.0/classes/OpenCVMat.html">OpenCVMat</a>, and <a href="http://www.antillia.com/sol9.2.0/classes/OpenCVImageInfo.html">OpenCVImageInfo</a> classes.
<br>
<br>
<table style="border: 1px solid red;">
<tr><td>
<font color="black" size=2>
<i>
Please see https://github.com/opencv/opencv/wiki/ChangeLog#version420<br>
Breaking changes:<br>
Disabled constructors for legacy C API structures.<br><br>
</i>
In OpenCV-4.2.0, the following naive code will cause a compilation error.<br><br>
 cv::Mat mat;<br>
 ...<br>
</font>
<font color="red" size=2>
 IplImage ipl = mat;  //Error<br>
</font>
<br>
<font size=2>
 The above line should be rewritten like this:<br><br>
 IplImage ipl = cvIplImage(mat); //OK<br>
<br>
</font>
</td></tr>
</table>
<br>
In sol9-2.1.2, we have added a <a href="https://pjreddie.com/darknet/yolo/">YOLO</a> C++ sample program: <br><br>
<a href="http://www.antillia.com/sol9.2.0/sol9.2.0samples/yolov3/YoloObjectDetector.html">YoloObjectDetector</a> 
<br>
<br>
, which is based on <b>Detector</b> class in <i>yolo_v2_class.hpp</i> in include folder of <a href="https://gitee.com/small_zhao_single_assists/darknet">darkent-master</a>.

<br>
In sol9-2.1.3, we have added another <a href="https://pjreddie.com/darknet/yolo/">YOLO</a> C++ sample program: <br><br>
<a href="http://www.antillia.com/sol9.2.0/sol9.2.0samples/yolov3/CustomYoloObjectDetector.html">CustomYoloObjectDetector</a> 
<br>
<br>
, which is based on C++ <a href="http://www.antillia.com/sol9.2.0/classes/Detector3.html">Detector3</a> class written by C APIs of dector.c, image.c, etc. in darknet-master/src folder of <a href="https://gitee.com/small_zhao_single_assists/darknet">darkent-master</a>.

<br>
<br>
In the latest sol9-2.1.4, we have added another simple YOLO C++ sample program  based on C++ <a href="http://www.antillia.com/sol9.2.0/classes/Detector3.html">Detector3</a>: <br><br>
<a href="http://www.antillia.com/sol9.2.0/sol9.2.0samples/yolov3/DetectedObjectHTMLFileGenerator.html">DetectedObjectHTMLFileGenerator</a> 
<br>
<!--
<br>
<br>
<font size=2>
<b>Download:
<br>
<br>
<a href="Javascript:confirmation('Are you sure you want to download SOL9 Library?', 'http://www.antillia.com/sol9.2.0/sol9-2.1.5-vs2019-win10-version-1903');">
SOL9-2.1 C++ Class Library for Windows 10 (Library & Samples)</a>
<font size=2>(sol9-2.1.5-vs2019-win10-version-1903</font><font color="red" size=2> #2020.02.10</font>)

<br>
<br>
-->
<a href="Javascript:confirmation('Are you sure you want to download SOL9 Library?', 'http://www.antillia.com/sol9.2.0/sol9.2.0.74-vs2017-win10-april-2018-update');">
SOL9.2.0 C++ Class Library for Windows 10 (Library & Samples)</a>
<font size=2>(sol9.2.0.74-vs2017-win10-april-2018-update</font><font color="red" size=2> #2018.12.31</font>)
</b>
<br>
<br>
<br>
</font>
<font size=2 >
 In the latest sol9-2.1.0 library for Visual Studio 2019 on Windows 10 April 2018 Update,
we have updated a lot of Makefiles of the library sample programs to be compiled on VS2019 and to support opencv-4.1.0. 
<br>
<br>
</font>
<!-- 
-->
<br>
<font size=2>
<b>1.3 SOL9-2.1.0 <font size = 2 color="red"></font></b><br>


SOL9 C++ Class Library 2.0 (SOL9-2.1.0) is an upgrade version of the previous SOL9 Library.
<br>
</font>
<b><font size = 2 color="red">Note:<br></font>
<font size = 2>

 1. SOL9 2.0 supports multiple charsets of ASCII and UNICODE.<br>
 2. SOL9 2.0 classes have been implemented on C++ header files only using inline member functions.<br>
 3, SOL9 2.0 applications never need a SOL9 specific static library.<br> 
 4. SOL9 2.0 classes have been developed based on the previous SOL9 Asciicode and Unicode version.<br>
</b>
</font>

<br>
<br>
<!--
<font size=2>
<b>1.4 SOL9 2.0 History<br>
</b>
 Please see the page <a href="http://www.antillia.com/sol9.2.0/history.html">SOL9 Class Library History</a>
 <br>
</font>
<br>
<br>
<font size=3>
-->

<hr noshade color = "gray">
<b>
2 How to install the SOL9 <br>
</b>

<font size=2 color="black">
You can get a zip file sol9-2.1.0.zip by downloading, so you simply
unzipp it by WinZip program. For example, by unzipping on the root directory on C 
drive, you get the two directories:
<br>
<!--
<pre>
-->
<b>C:\so9-2.1.0\usr\include\sol </b><br>
 - includes all C++ header files for SOL9-2.1.0<br>
<br>
<b>C:\sol9-2.1.0\usr\src\</b><br>
 - includes all sample program files for SOL9-2.1.0,
<br>
<br>
<font size=3>
<hr noshade color = "gray">
<b>
3 How to create a new project.
</font><br>
</b>
</font>
<font size=2>
 When you create a new project and compile the program on SOL9 in Microsoft Visual Studio(VS)
 environment, please note the following rules.
<br>
<br>
<b>
3.1 You have to specifiy [Multithreaded] runtime library in C/C++ Code
generation pane.</b><br>

(1) Select [Project] item in the menubar of VS.<br>
(2) Select [Setting] item in the pulldown menu dispayed by (1).<br>
(3) Select [C/C++] tab in the rightside pane of the dialogbox displayed by
(2) <br>
(4) Select [Code generation] item in the combobox for [Category] item in
    the pane displayed by (3).<br>
(5) Select [Multithreaded] item in the combobox for [Runtime Library] item
    in the pane displayed by (4).<br>

<br><b>
3.2 You have to set correct paths for include files and a library file of
SOL9.</b><br>

(1) Select [Tool] item in the menubar of VS.<br>
(2) Select [Option] item in the pulldown menu displayed by (1)<br>
(3) Select [Directory] pane the dialogbox displayed by (2).<br>
(4) Add the path for SOL9 include files in th listbox displayed by
    selecting [include files] item in the combobox of [Directories].
 Maybe you add a line something like this.<br>

&nbsp;&nbsp;&nbsp;&nbsp;c:\usr\include

<br>
<br>
<b>
3.3 You have to specifiy the libraries
<br>
</b>
<font size=2 color="red">Please specify the following libraries:<br></font>
<font size=2 color="red">
 [comctl32.lib ws2_32.lib iphlpapi.lib version.lib crypt32.lib cryptui.lib wintrust.lib pdh.lib shlwapi.lib psapi.lib</font>].</b><br>
<br>

(1) Select [Project] item in the menubar of VS.<br>
(2) Select [Setting] item in the pulldown menu dispayed by (1).<br>
(3) Select [Link] tab in the rightside pane of the dialogbox displayed by
(2).<br>
(4) Select [General] item in the combobox for [Category] item in
    the pane displayed by (3).<br>
(5) Insert the libraies [<font size=2 color="red">comctl32.lib ws2_32.lib iphlpapi.lib version.lib crypt32.lib cryptui.lib wintrust.lib pdh.lib shlwapi.lib psapi.lib</font>] into the
text field of name [Object/Libray/Module].<br>

<br>
<b>
 Please don't forget to write  Main (not main) function in your
 <font color="brown">Windows </font>program, because it is a program entry point of SOL9.<br>
</b>
</font>

<br>
<!--
<b>
<font size=2 color="black">
3.4 You have to define 'COMMONCONTROLS_V6'
</font>
<br>
</b>
<font size=2 color="black">If you want to use Common-Controls version 6.0.0.0 in Windows applications,
 please define COMMONCONTROLS_V6 at the top of your application program in the following way:<br></font>
<br>
<table width="100%" border=1 style='border-collapse: collapse;'>
<tr><td bgcolor="#eeeeff">
<font size=2 color="navy">
//SomethingApplication.cpp<br>
</font>
<font size=2 color="red">

#define COMMONCONTROLS_V6<br>
</font>
<font size=2 color="navy">

#include &lt;sol/ApplicationView.h&gt;<br>
#include &lt;sol/PushButton.h&gt;<br>

...<br>
class SomethingApplication :public ApplicationView {<br>
...<br>
};<br>
</font>
</td></tr></table>
<br>
 -->
 
<font size=3>
<hr noshade color = "gray">
<b>
4  Kittle cattle in Windows
</font><br>
</b>
<br>
<font size=2>
<a href="#4.1">4.1 How to get a Windows Version?</a><br><br>
<a href="#4.2">4.2 How to render a text on Direct3D11?</a><br><br>
<a href="#4.3">4.3 How to render an image on Direct3D11?</a><br><br>
<a href="#4.4">4.4 How to render a geometrical shape on Direct3D11?</a><br><br>
<a href="#4.5">4.5 Effect interfaces have passed away in Direct3D11?</a><br><br>
<a href="#4.6">4.6 How to render a multitextured cube in OpenGL?</a><br><br>
<a href="#4.7">4.7 How to use OpenGL Shader Language feature of OpenGL 2 based on GLEW?</a><br><br>
<a href="#4.8">4.8 How to use GL_ARB_vertex_buffer_object extension of OpenGL based on GLEW?</a><br><br>
<a href="#4.9">4.9 How to change RGB-Color, EyePosition, and LightPosition for 3D-Shapes in OpenGL?</a><br><br>
<a href="#4.10">4.10 How to draw shapes by using multiple PipelineStates in Direct3D12?</a><br><br>
<a href="#4.11">4.11 How to render a textured cube in Direct3D12?</a><br><br>
<a href="#4.12">4.12 Is there a much simpler way to upload a texture in Direct3D12? </a><br><br>
<a href="#4.13">4.13 How to render a text on Direct3D12?</a><br><br>
<a href="#4.14">4.14 How to render multiple textured rectangles in Direct3D12?</a><br><br>
<a href="#4.15">4.15 How to use multiple ConstantBufferViews to render translated shapes in Direct3D12?</a><br><br>
<a href="#4.16">4.16 How to render MultiTexturedCubes in Direct3D12?</a><br><br>
<a href="#4.17">4.17 How to render a star system model in Direct3D12? </a><br><br>

<a href="#4.18">4.18 How to render multiple materialized shapes in OpenGL?</a><br><br>
<a href="#4.19">4.19 How to render a textured sphere in OpenGL?</a><br><br>
<a href="#4.20">4.20 How to render a star system model in OpenGL? </a><br><br>

<a href="#4.21">4.21 How to blur an image in OpenCV?</a><br><br>
<a href="#4.22">4.22 How to sharpen an image in OpenCV?</a><br><br>
<a href="#4.23">4.23 How to detect faces in an image in OpenCV? </a><br><br>
<a href="#4.24">4.24 How to detect features in an image in OpenCV? </a><br><br>
<a href="#4.25">4.25 How to enumerate Video Input Devices to use in OpenCV VideoCapture?</a><br><br>
<a href="#4.26">4.26 How to map cv::Mat of OpenCV to a shape of OpenGL as a texture? </a><br><br>
<a href="#4.27">4.27 How to read a frame buffer of OpenGL and convert it to cv::Mat of OpenCV?</a><br><br>
<a href="#4.28">4.28 How to transform an image by a dynamic color filter in OpenCV? </a><br><br>
<a href="#4.29">4.29 How to render a textured sphere with Axis, Eye, and Light Positioner in OpenGL? </a><br><br>
<a href="#4.30">4.30 How to detect a bounding box for an object in a cv::Mat of OpenCV? </a><br><br>
<a href="#4.31">4.31 How to detect people in a cv::Mat image by using HOGFeature of OpenCV? </a><br><br>
<a href="#4.32">4.32 How to create CustomYoloObjectDetector class based on C APIs of darknet-master? </a><br><br>
<a href="#4.33">4.33 How to create DetectedObjectHTMLFileGenerator for YOLO by using SOL Detector3 and a template.html file?
</a><br><br>

<br>

<font size=2><a href="http://www.antillia.com/sol9.2.0/4.1.html" name="4.1"><br>4.1 How to get a Windows Version?</a><br>

As you know, in Windows 8.1 and later Windows version, GetVersion(Ex) APIs have been deprecated. 
Those APIs would not return a correct version value under those systems, without specifying 
a supportedOS tag for Windows 8.1 or Windows 10 in the application manifest file. (<a href="https://msdn.microsoft.com/en-us/library/windows/desktop/dn302074(v=vs.85).aspx">
Operating system version changes in Windows 8.1 and Windows Server 2012 R2),</a>.

As for a sample program using a manifest file with the supportedOS tags, please see <a href="http://www.antillia.com/sol9.2.0/sol9.2.0samples/WindowsVersion.html">WindowsVersion</a>.

<br>
If you are familiar with WMI programming, it may be better to use WMI Win32_OperatingSystem class to get the correct Windows version (OS Name).<br>

In the latest SOL9.2.0 library, we have implemented <a href="http://www.antillia.com/sol9.2.0/classes/SWbemQueryOperatingSystem.html">SOL::SWbemQueryOperatingSystem</a> C++ class to query various information on Windows operating system.
<br>  
This example based on the C++ class shows how to get "Caption" property, which contains a Windows OS name, and All ("*") properties of Windows System.
See also a GUI version <a href="http://www.antillia.com/sol9.2.0/sol9.2.0samples/SolOperatingSystemViewer.html">SolOperatingSystemViewer</a>
<br>
</font>
<br>
<a href="http://www.antillia.com/sol9.2.0/4.1.html"><img src="http://www.antillia.com/sol9.2.0/images/SWbemQueryOperatingSystemApplet.png"></a>
<br>
<br>
<font size=2><a href="http://www.antillia.com/sol9.2.0/4.2.html" name="4.2"><br>4.2  How to render a text on Direct3D11? </a><br>
As you maybe know, Direct3D10 has ID3DX10Font interface to render a text, but Direct3D11 has no corresponding interface something like
a ID3DX11Font.<br> 
On Direct3D11, you will use IDWrite interfaces, for example IDWriteTextFormat or IDWriteTextLayout, to draw a text on 
an instance of ID2D1RenderTarget created by ID2D1Factory interface.
See aslo our directx samples: <a href="http://www.antillia.com/sol9.2.0/sol9.2.0samples/directx/DirectWriteTextFormat.html">DirectWriteTextFormat</a>. 
and <a href="http://www.antillia.com/sol9.2.0/sol9.2.0samples/directx/DirectWriteTextLayout.html">DirectWriteTextLayout</a>.<br>
<br>
This example based on SOL Direct2D1, DirectWrite, Direct3D11 classes shows how to render a text string on Direct3D11 environment.

</font>
<br>
<br>
<a href="http://www.antillia.com/sol9.2.0/4.2.html"><img src="http://www.antillia.com/sol9.2.0/images/Direct3DX11TextRendering.png"  ></a>
<br>
<br>
<font size=2><a href="http://www.antillia.com/sol9.2.0/4.3.html" name="4.3"><br>4.3 How to render an image on Direct3D11? </a><br>
 Direct3D10 has ID3DX10Sprite interface to draw an image, but Direct3D11 has no corresponding interface something like
a ID3DX11Sprite.
On Direct3D11, to read image files, you will use the WIC (Windows Imaging Component) interfaces, and to display the read images,
 an instance of ID2D1Bitmap created by WIC interfaces, and ID2D1RenderTarget created by ID2D1Factory interface.
See aslo our directx samples: <a href="http://www.antillia.com/sol9.2.0/sol9.2.0samples/directx/Direct2DBitmap.html">Direct2DBitmap</a>. 
and <a href="http://www.antillia.com/sol9.2.0/sol9.2.0samples/directx/WICBitmapScaler.html">WICBitmapScaler</a>.<br>
<br>
This example based on SOL Direct2D1, WIC, Direct3D11 classes shows how to render an image file on Direct3D11 environment.

</font>
<br>
<br>
<a href="http://www.antillia.com/sol9.2.0/4.3.html">    <img src="http://www.antillia.com/sol9.2.0/images/Direct3DX11ImageRendering.png" ></a>
<br>
<br>
<font size=2><a href="http://www.antillia.com/sol9.2.0/4.4.html" name="4.4"><br>4.4 How to render a geometrical shape on Direct3D11? </a><br>
 Direct3D 10 has ID3DX10Mesh interface to store vertices and indices data of geometrical shapes,
  and to draw the shapes by using ID3D10Effect and related ID3D10EffectVaraible interfaces,
 but, Direct3D 11 has no corresponding interface something like ID3DX11Mesh.<br>
 Direct3D10 Sample C++ programs also provides some optional APIs based on ID3DX11Mesh to create typical shapes such as Box, Cylinder, Polygon, Sphere, Torus, Teapost
 (See: Microsoft DirectX SDK (June 2010)\Samples\C++\DXUT\Optional\DXUTShape.h)
 , but Direct3D 11 has no optional creation APIs for such shapes.<br> 
Fortunately, in almost all cases, the ID3DXMesh interface will be replaced by a pair of vertexBuffer and indexBuffer which are Direct3D11 ID3D11Buffers respectively.<br>
On Direct3D11 environment. you will be able to write APIs to draw the typical geometrical shapes, by using ID3D11Buffer interface.<br>

In fact, on the latest SOL9.2.0.41 library, 
we have implemented the following C++ classes based on the DXUT\Optional\DXUTShape.cpp for Direct3D 11:<br>
This example shows how to render a sphere on Direct3D11 environment.<br>
<br>
</font>
<a href="http://www.antillia.com/sol9.2.0/4.4.html"><img src="http://www.antillia.com/sol9.2.0/images/Direct3DX11SphereBuffer.png" ></a>
<br>
<br>
<font size=2><a href="http://www.antillia.com/sol9.2.0/4.5.html" name="4.5"><br>4.5 Effect interfaces have passed away in Direct3D11? </a><br>
It could be so. In fact, you cannot find a 'd3d11effect.h' file for Direct3D 11 effect interfaces in the standard include folder
<br><br> 
'C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include'.
<br><br>
  However, you can see an optional Direct3D 11 effect library
 in the sample folder 
<br><br>
'C:\Program Files (x86)\Microsoft DirectX SDK June 2010)\Samples\C++\Effects11'.
<br><br> 
This implies that Direct3D 11 effect interfaces have been graded down to the optional sample from the standard. By the way,
what differences are there on the interfaces between Direct3D10 and Direct3D11? 
The methods of those interfaces are basically same, but Direct3D11(Effects11) has no EffectPool interface.<br> 
 In the latest sol9.2.0.43 library, we have implemented the C++ classes for the optioal Direct3D11 effect interfaces.<br>
This example shows how to use Direct3DX11Effect classes on Direct3D11 platform.<br>
</font>
<br>
<br>
<a href="http://www.antillia.com/sol9.2.0/4.5.html">  <img src="http://www.antillia.com/sol9.2.0/images/Direct3DX11MultipleLightedSpheresEffect.png" ></a>
<br><br>
<font size=2><a href="http://www.antillia.com/sol9.2.0/4.6.html" name="4.6"><br>4.6 How to render a multitextured cube in OpenGL? </a><br>
&nbsp; We have C++ class OpenGLMultiTexturedCube to render a cube textured by multiple JPG or PNG image files.<br>
&nbsp;This is a simple sample program based on that class, and six JPG files for the cube fases.<br>
&nbsp;In this program you can rotate the textured cube by Left and Right keys.<br>  
<br>
</font>
<a href="http://www.antillia.com/sol9.2.0/4.6.html">  <img src="http://www.antillia.com/sol9.2.0/images/MultiJPGTexturedCubeRotationByKeyInput.png" ></a>
<br><br>

<font size=2><a href="http://www.antillia.com/sol9.2.0/4.7.html" name="4.7"><br>4.7 How to use OpenGL Shader Language feature of OpenGL 2 based on GLEW? </a><br>
&nbsp; In SOL2.0.48 ,we have updated our OpenGL C++ classes to use GLEW in order to create a context-version-dependent context, and to use the features of OpenGL Shader Language.<br>  
&nbsp;  Currently, the default major version and the minor version for OpenGLRenderContex class are 3 and 1 respectively.
You can also specify those versions in the the file 'oglprofile.ogl' file placed in a folder of the executable program.<br>
&nbsp;This is a very simple sample program to use OpenGLProram, OpenGLFragmentShader, and OpenGLVertexShader, 
and OpenGLVertexAttribute classes to draw a multicolored triangle. <br>
<br>
</font>

<a href="http://www.antillia.com/sol9.2.0/4.7.html">  <img src="http://www.antillia.com/sol9.2.0/images/MultiColoredTriangleShader.png" ></a>
<br>
<br>
<font size=2><a href="http://www.antillia.com/sol9.2.0/4.8.html" name="4.8"><br>4.8 How to use GL_ARB_vertex_buffer_object extension of OpenGL based on GLEW? </a><br>
 In the lastest SOL9.2.0 library, we have added new classes OpenGLBufferARB, OpenGLBufferedShapd, OpenGLIndexBufferARB, and OpenGLVertexBufferARB to 'sol/openglarb/' folder
  to support GL_ARB_vertex_buffer_object extension in GLEW.<br>
 This is a very simple sample program to draw OpenGLColoredCube by using those classes. <br>

</font><br>

<a href="http://www.antillia.com/sol9.2.0/4.8.html">  <img src="http://www.antillia.com/sol9.2.0/images/BufferedGradientColoredCube.png"></a>
<br>

<font size=2><a href="http://www.antillia.com/sol9.2.0/4.9.html" name="4.9"><br>4.9 How to change RGB-Color, EyePosition, and LightPosition for 3D-Shapes in OpenGL? </a><br>
 In the lastest SOL9.2.0 library, we have added new classes Positioner, ColorPositioner, EyePositioner and LightPositiner to 'sol/' folder.
 Those have been implemented by Windows ScrollBar triplet, which are based on SOL::ColorMixer class.
 This is a very simple sample program to draw Glut SolidTors by using those classes. <br>
</font>
<br>
<a href="http://www.antillia.com/sol9.2.0/4.9.html">  <img src="http://www.antillia.com/sol9.2.0/images/TorusWithColorEyeAndLightPositioner.png" ></a>
<br>

<font size=2><a href="http://www.antillia.com/sol9.2.0/4.10.html" name="4.10"><br>4.10 How to draw shapes by using multiple PipelineStates in Direct3D12? </a><br>
 In the lastest SOL9.2.0 library, we have added new classes to support Direct3D12 on Windows 10 to 'sol/direct3d12' folder.
 We have implemented the Direct3D12 in a similar way of our Direct3D11 classes to keep compatibilies between them.  <br>
 This is a very simple sample program to draw a wireframed sphere and a solid torus moving on a circular orbit by using two PipelineState objects,
  and TimerThread. <br>
</font>
<br>
<a href="http://www.antillia.com/sol9.2.0/4.10.html">  <img src="http://www.antillia.com/sol9.2.0/images/Direct3D12OrbitersWithMultiplePipelineStates.png" ></a>
<br>
<br>
<font size=2><a href="http://www.antillia.com/sol9.2.0/4.11.html" name="4.11"><br>4.11 How to render a textured cube in Direct3D12? </a><br>
 In Direct3D12, it is not so eay to render a textured shape rather than Direct3D11, because in standard D3D12 programming environment,
 you have to live without D3DX (see:<a href="https://blogs.msdn.microsoft.com/chuckw/2013/08/20/living-without-d3dx/">Living without D3DX</a>).
For example, there are no <i>D3DX12CreateShaderResourceViewFromFile</i> or something similar APIs to create a shaderResourceView from an image file
 or an image on memory in D3D12X (d3d12x.h).
<br>
  Fortunately, however, you can find some very convenient APIs to read an image file, and to upload the correspoing texture
 in the following extension package from Microsoft:<br><br>
 <a href="https://github.com/Microsoft/DirectXTK12">Microsoft/DirectXTK12 </a><br><br>
 It teaches us the following:<br><br>
1. Use <i>CreateTextureFromWIC</i> API, which is an image file reader based on WIC(Windows Imaging Component) to create D3D12 intermediate texture resource 
from a standard image file such as BMP, JPG, PNG, etc.<br>
2. Use <i>UpdateSubresources</i> API to upload the intermediate texture resource created by <i>CreateTextureFromWIC</i> to a target texture resource.<br>   
<br>
 We have updated class WICBitmapFileReader and implemented new C++ class Direct3D12Subresources to use those APIs.<br>
 This is a very simple sample program to render a BMP textured cube by using those classes,
<br><br>
<a href="http://www.antillia.com/sol9.2.0/4.11.html">  <img src="http://www.antillia.com/sol9.2.0/images/Direct3D12BMPTexturedCube.png" ></a>
<br>

<font size=2><a href="http://www.antillia.com/sol9.2.0/4.12.html" name="4.12"><br>4.12 Is there a much simpler way to upload a texture in Direct3D12?
</a><br>
 In the above Direct3D12BMPTexturedCube sample program, we have used very complicated WICBitmapFileReader and Direct3D12Subresources classes, 
 which are based on the source files in Microsoft/DirectXTK12 toolkit.<br>
It is much better to be able to write much simpler classes to read an image file and to upload a texture, 
even if they may have some restrictions, by using our C++ class library, without the toolkit.<br>
In fact, we are able to write the following classes which are simpler than the classes based on the toolkit:
<br><br>
1 <a href="http://www.antillia.com/sol9.2.0/classes/ImageFileReader.html">ImageFileReader</a> to read an image file reader for PNG and JPG only written by using JPGFileReader and PNGFileReader classes.<br>
2 <a href="http://www.antillia.com/sol9.2.0/classes/Direct3D12IntermediateResource.html">Direct3D12IntermediateResource</a> to upload an intermedaite texture resource to a desitination texture resource.<br>
<br>
This is a very simple sample program to render a PNG textured cube by using the simpler classes, 
<br>
</font>
<br>
<a href="http://www.antillia.com/sol9.2.0/4.12.html">  <img src="http://www.antillia.com/sol9.2.0/images/Direct3D12PNGTexturedCubeByIntermediateResourceAndImageFileReader.png" ></a>
<br>

<font size=2><a href="http://www.antillia.com/sol9.2.0/4.13.html" name="4.13"><br>4.13 How to render a text on Direct3D12?
</a><br>
 As you know, Direct3D11 and Direct3D12 have no interfaces something like ID3DX11Font or ID3DX12Font to render a text.
  But as shown in <a href="#4.2">How to render a text on Direct3D11</a>, you can use IDWriteTextFormat or IDWriteTextLayout,
   to draw a text on an instance of ID2D1RenderTarget created by ID2D1Factory interface.<br>

In Direct3D12, you can use ID11On12Device to create D3D11Resource (wrappedResource), and render a text by using the wrappedResource.<br>
See <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/dn913195(v=vs.85).aspx">Direct3D 11 on 12</a> <br>

In the latest SOL9.2.0, we have implemented the following two classes to support ID11On12Device interface.<br>
<br>
1. <a href="http://www.antillia.com/sol9.2.0/classes/Direct3D11On12Device.html">Direct3D11On12Device</a> to create an ID3D11Resource (ID3D11 wrapped resource).<br><br>
2. <a href="http://www.antillia.com/sol9.2.0/classes/Direct3D11On12WrappedResource.html">Direct3D11On12WrappedResource</a> to represent the ID3d11 wrapped resource.<br>
<br>

This example based on SOL DirectWrite(DXGI), Direct2D1, Direct3D12 classes shows how to draw a text string on a torus rendered on Direct3D12.

<br>
</font>
<br>
<a href="http://www.antillia.com/sol9.2.0/4.13.html">  <img src="http://www.antillia.com/sol9.2.0/images/Direct3D11On12TextLayout.png" ></a>
<br>

<font size=2><a href="http://www.antillia.com/sol9.2.0/4.14.html" name="4.14"><br>4.14 How to render multiple textured rectangles in Direct3D12? </a><br>
In order to render multiple textured shapes,  we have to create multiple instances of Direct3DX12Shape, Direct3D12Texture2D and 
Direct3D12ShaderResourceViews. Of course, we also have to create a rootSignature object having the number of descriptors corresponding to 
the multiple ShaderResourceViews.<br>
<br>
 We have updated class <a href="http://www.antillia.com/sol9.2.0/classes/Direct3D12RootSignature.html">Direct3D12RootSignature</a>to be able to specify the number
  of ConstantBufferViews and the number of ShaderResourceViews respectively.<br> 
 <br>
 This is a very simple sample program to render four PNG textured rectangles by using those classes,
<br><br>
<a href="http://www.antillia.com/sol9.2.0/4.14.html">  <img src="http://www.antillia.com/sol9.2.0/images/Direct3D12MultiPNGTexturedRectangles.png" ></a>
<br>

<font size=2><a href="http://www.antillia.com/sol9.2.0/4.15.html" name="4.15"><br>4.15 How to use multiple ConstantBufferViews to render translated shapes in Direct3D12? </a><br>
 
Imagine to render some geometrical shapes(Box, Sphere, Torus, Cylinder and so on) in the translated positions 
on WorldViewProjection system in Direct3D12.<br>
 In Direct3D11, it is simple and easy as shown in 
 <a href="http://www.antillia.com/sol9.2.0/sol9.2.0samples/direct3d11/Direct3DX11MultipleLightedShapesBuffer.html">Direct3DX11MultipleLightedShapesBuffer</a>
 
<br> 
In Direct3D11, we only have to create one ConstantBufferView for multiple shapes, whereas in Direct3D12  we have to create multiple
 ConstantBufferViews to specify 
the translated position on WorldViewProjection system for each shape, and also a RootSignature having the number of descriptors corresponding to 
the multiple ConstantBufferViews.<br>
<br>
 This is a very simple sample program to render Box, Sphere, Torus, and Cylinder. 
<br><br>
<a href="http://www.antillia.com/sol9.2.0/4.15.html">  <img src="http://www.antillia.com/sol9.2.0/images/Direct3D12LightedShapesWithMultipleConstantBufferViews.png" ></a>
<br>


<font size=2><a href="http://www.antillia.com/sol9.2.0/4.16.html" name="4.16">
<br>4.16 How to render MultiTexturedCubes in Direct3D12? </a><br>
 
Imagine to render a cube textured with multiple image files in Direct3D12.<br>
The sample program of <a href="http://www.antillia.com/sol9.2.0/4.14.html" name="4.14">4.14 How to render multiple textured rectangles in Direct3D12? </a>
is helpful for it.
As you can easily see, you will have to do the following things to create a multiTexturedCube:<br><br>
1. Create a set of VertexBuffers and IndexBuffers for six square faces of a cube.<br>
2. Create a set of Texture2D resources for six faces of the cube.<br>  
3. Create a set of Image resources for six faces of the cube.<br>
4. Create a set of ShaderResourceViews for the texture2Ds. <br>
<br>.
 To clarify the problem, we have implemented the following C++ classes.<br> 
<a href="http://www.antillia.com/sol9.2.0/classes/Direct3DX12MultiTexturedShape.html">Direct3DX12MultiTexturedShape</a><br><br>
<a href="http://www.antillia.com/sol9.2.0/classes/Direct3DX12TexturedFace.html">Direct3DX12TexturedFace</a><br><br>
<a href="http://www.antillia.com/sol9.2.0/classes/Direct3DX12MultiTexturedBox.html">Direct3DX12MultiTexturedBox</a><br><br>
<a href="http://www.antillia.com/sol9.2.0/classes/Direct3DX12MultiTexturedCube.html">Direct3DX12MultiTexturedCube</a><br><br>

 This is a very simple sample program to render two MultiTexturedCubes. 
<br><br>
<a href="http://www.antillia.com/sol9.2.0/4.16.html">  <img src="http://www.antillia.com/sol9.2.0/images/Direct3D12MultiTexturedCubes.png" ></a>
<br>

<br>
<font size=2><a href="http://www.antillia.com/sol9.2.0/4.17.html" name="4.17">
<br>4.17 How to render a star system model in Direct3D12? </a><br>
<br>
Imagine to render a star system model like our solar system on Direct3D12.<br>
Since we are neither astrnomers nor model designers, apparently, 
it is difficult to draw a realistic solar system model, even if a lot of detailed planets trajectories data would have been given.<br>
To simpify a story, we here assume an imaginary simple star system, say Scintilla, which  consists of a single
sun-like sphere star and some planet-like spheres rotating on circular oribits around the sun star, and
furthermore, to avoid confusion, we do not care the complicated reflection light problem from the sun of the planets.<br> 
We simly have to the following things,<br><br>

1 Create multiple Direct3DX12Sphere instances to describe spheres for the central star and planets.<br>
2 Create multiple <a href="http://www.antillia.com/sol9.2.0/classes/Direct3D12TransformLightConstantBufferView.html">Direct3D12TransformLightConstantBufferView</a> instances to describe the positions
  for the star and the planets in WorldViewProjection systems.<br>
3 Create multiple Direct3DX12Circle instances to define circular orbits for the planets.<br>
4 Create a Direct3D12TimerThread to move planets on the circular orbits.<br>
5 Draw the sun star and planets rotating around the star by the ConstantBufferViews and the TimerThread.<br>
<br>  
The following Direct3D12ScintillaStarSystem is a simple example to draw a star system model.
<br><br>
<a href="http://www.antillia.com/sol9.2.0/4.17.html">  <img src="http://www.antillia.com/sol9.2.0/images/Direct3D12ScintillaStarSystem.png" ></a>
<br>
<!-- 2017.0225 -->
<br>
<font size=2><a href="http://www.antillia.com/sol9.2.0/4.18.html" name="4.18">
<br>4.18 How to render multiple materialized shapes in OpenGL? </a><br>
<br>
 As you know, in OpenGL, there is a glMaterial API to set material properties.<br>
In the latest sol9.2.0, we have implemented <a href="http://www.antillia.com/sol9.2.0/classes/OpenGLMateria.html">OpenGLMateria</a> class to 
store material properites:face, ambient, diffuse, specular, emission, shininess.
<br>
<br>  
The following MaterializedSpheresRotationByTimerThread is a simple example to draw multiple matreialized sphere
by using OpenGLMateria, and rotate them by OpenGLTimerThread.
<br><br>
<a href="http://www.antillia.com/sol9.2.0/4.18.html">  <img src="http://www.antillia.com/sol9.2.0/images/MaterializedSpheresRotationByTimerThread.png" ></a>
<br>

<br>
<font size=2><a href="http://www.antillia.com/sol9.2.0/4.19.html" name="4.19">
<br>4.19 How to render a textured sphere in OpenGL?</a><br>
 Imagine to render a textured sphere.
 In OpenGL, there are some methods to map a texture to a solid sphere.<br><br>
1. To use gluSphere and gluQuadricTexture APIs in OpenGL GLU library.
<br> See <a href="https://www.khronos.org/opengl/wiki/Texturing_a_Sphere">Texturing a Sphere</a>.
<br><br>
2. To write your own code to draw a sphere with texture coordinates.
<br>See <a href="http://www.codeincodeblock.com/2011/06/texture-map-in-solid-sphere-using.html">Texture map in solid sphere using GLUT(OpenGL) 
</a>.
<br>
<br>
Please note that you cannot use glutSolidSphere API of OpenGL GLUT library to map a texture on the sphere, 
because the API doesn't support texture coordinates.<br> 
 In the latest sol9.2.0 library, we have implemented <a href="http://www.antillia.com/sol9.2.0/classes/OpenGLTexturedSphere.html">OpenGLTexturedSphere</a> class based on the first method.<br>
<br>  
The following TexturedSphereRotationByKeyInput is a simple example to draw a textured shpere and rotate it by Left or Rigth keys.<br>
<br>
In this example, we have used the world map of 'world.topo.bathy.200412.3x5400x2700.jpg' file in the following page.<br>
<a href="http://visibleearth.nasa.gov/view.php?id=73909">NASA VISIBLE EARTH</a><br>
December, Blue Marble Next Generation w/ Topography and Bathymetry<br>
Credit: Reto Stockli, NASA Earth Observatory<br>
<br><br>
<a href="http://www.antillia.com/sol9.2.0/4.19.html">  <img src="http://www.antillia.com/sol9.2.0/images/TexturedSphereRotationByKeyInput.png" ></a>
<br>
<br>
<br>
<font size=2>
We have also used Viking's Mars 'mar0kuu2.jpg' created by Caltech/JPL/USGS in the <a href="https://maps.jpl.nasa.gov/mars.html">SOLAR SYSTEM SIMULATOR</a>.
</font>
<br>
<br>
<a href="http://www.antillia.com/sol9.2.0/4.19.html">  <img src="http://www.antillia.com/sol9.2.0/images/TexturedSphereRotationByKeyInput_Mars.png" ></a>

<br>
<br>
<font size=2>
We have also used Jupiter 'PIA07782_hires.jpg' in the <a href="https://www.jpl.nasa.gov/spaceimages/details.php?id=PIA07782">JPL Cassini's Best Maps of Jupiter</a>.
</font>
<br>
<br>
<a href="http://www.antillia.com/sol9.2.0/4.19.html">  <img src="http://www.antillia.com/sol9.2.0/images/TexturedSphereRotationByKeyInput_Jupiter.png" ></a>

<br>
<br>

<font size=2><a href="http://www.antillia.com/sol9.2.0/4.20.html" name="4.20">
<br>4.20 How to render a star system model in OpenGL? </a><br>
<br>
 We have arleady written sample program <a href="#4.17">Direct3D12ScintillaStarSystem</a> to render a star system model in Direct3D12,<br>
In OpenGL, we can also draw a simple star system model like our solar system.  
As the example of Direct3D12, to simpify a story, we assume an imaginary star system which consists of a single sun-like sphere star 
and some planet-like spheres rotating on circular oribits around the sun star
, and furthermore, to avoid confusion, we do not care the light direction and reflection light problem of sun and the planets.
 
<br>  
The following StarSystemModel is a simple example to draw a star system model.
<br><br>
<a href="http://www.antillia.com/sol9.2.0/4.20.html">  <img src="http://www.antillia.com/sol9.2.0/images/StarSystemModel.png" ></a>
<br>


<br>
<font size=2><a href="http://www.antillia.com/sol9.2.0/4.21.html" name="4.21">
<br>4.21 How to blur an image in OpenCV? </a><br>
<br>
 As you know, OpenCV has some image filter classes and image-blur APIs <a href="http://docs.opencv.org/2.4/doc/tutorials/imgproc/gausian_median_blur_bilateral_filter/gausian_median_blur_bilateral_filter.html">
Smoothing Images</a> such as:<br>
<br>
blur<br>
GaussianBlur<br>
medianBlur<br>
bilateralFilter<br>
<br>
 The following MedianBlur program is a simple example to blur an image based on mediaBlur funcition. <br>
The left pane is an orignal image, and the right pane is a blurred image created by a KernelSize trackbar control.
<br>  
<br><br>
<a href="http://www.antillia.com/sol9.2.0/4.21.html">  <img src="http://www.antillia.com/sol9.2.0/images/MedianBlur.png" ></a>
<br>

<br>
<font size=2><a href="http://www.antillia.com/sol9.2.0/4.22.html" name="4.22">
<br>4.22 How to sharpen an image in OpenCV? </a><br>
<br>
 As shown in <a href="https://en.wikipedia.org/wiki/Unsharp_masking#Digital_unsharp_masking">Unsharp masking</a>,
 Unsharp masking (USM) is one of the image sharpening techniques. It uses a smoothed (blurred), or "unsharp", negative image 
 to create a mask of the original image.<br>
The following imageSharpening program is a simple image sharpening example based on the USM technique, in which we have used the following two APIs: <br>
<br> 
1 GaussinaBlur to create a blurred mask image from an original image.<br>
<br>
2 addWeighted to combine the blurred image and the original image. <br>
<br>
The left pane is an orignal image, and the right pane is a sharpened image created by KernelSize and Sigma trackbar controls.
  
<br><br>
<a href="http://www.antillia.com/sol9.2.0/4.22.html">  <img src="http://www.antillia.com/sol9.2.0/images/ImageSharpening.png" ></a>
<br>
<br>
<br>
<font size=2><a href="http://www.antillia.com/sol9.2.0/4.23.html" name="4.23">
<br>4.23 How to detect faces in an image in OpenCV? </a><br>
<br>
 One of the most interesting feature of OpenCV is an image recognition or object detection, which is a very important technology
 in modern computer vision based systems.<br>
 For detail, please see the OpenCV documentation <a href="http://docs.opencv.org/2.4/modules/objdetect/doc/cascade_classification.html">
Cascade Classification Haar Feature-based Cascade Classifier for Object Detection</a>.<br><br>

 In the latest OpenCV version, the following two types of cascade classifiers are available:<br><br>
 <li>Harr Feature-based Cascade Classifier</li><br>
 <li>LBP(Local binary pattern) Cascade Classifier</li><br>
 
On these cascade classifiers, please check your OpenCV installed directory, for example, you can find folders including classifier files
 under the folder "C:\opencv3.2\build\etc".
<br> 
 The following SolObjectDetector is a simple object detection example. <br><br>
1 Select a folder which  contains Harr or LBP cascade classifiers by using a folder selection dialog.<br>
2 Select a cascade classifier xml file in a combobox.<br>
3 Open a target image file by using a file open dialog which can be popped up by Open menu item.<br>
4 Click Detect pushbutton.<br>
 
<br>
  
<br>Face detection of a cat.<br>
<a href="http://www.antillia.com/sol9.2.0/4.23.html">  <img src="http://www.antillia.com/sol9.2.0/images/SolObjectDetector1.png" ></a>
<br>
<br>
Face and eyes detection of a mannequin.<br>
<a href="http://www.antillia.com/sol9.2.0/4.23.html">  <img src="http://www.antillia.com/sol9.2.0/images/SolObjectDetector2.png" ></a>
<br>
<br>
Eyes detection of a Nioh.<br>
<a href="http://www.antillia.com/sol9.2.0/4.23.html">  <img src="http://www.antillia.com/sol9.2.0/images/SolObjectDetector3.png" ></a>
<br>
<br>
<!-- -->
<font size=2><a href="http://www.antillia.com/sol9.2.0/4.24.html" name="4.24">
<br>4.24 How to detect features in an image in OpenCV? </a><br>
<br>
</b>
 The latest OpenCV3.2.0 has a lot of various algorithms (C++ classes) to detect features in an image as shown below.<br>
 <img src="http://www.antillia.com/sol9.2.0/images/DetectorClasses.png">
  <br>
  <br>
We have implemented a simple GUI program SolFeatureDetector to use these detector classes to various images.<br>
You need the following operations to use this program.<br><br>
1 Open a target image file by using a file open dialog which can be popped up by Open menu item.<br>
2 Select a detector from  detectors combobox.<br>
3 Select a a color from a combobox color chooser.<br>
4 Click Detect pushbutton.<br>
5 Click Clear pushbutton to clear detected keypoints.
<br>
 
<br>
 
<br>Feature detection in a geometry image.<br>
<a href="http://www.antillia.com/sol9.2.0/4.24.html">  <img src="http://www.antillia.com/sol9.2.0/images/SolFeatureDetector1.png" ></a>
<br>
<br>
Feature detection in a cloud image.<br>
<a href="http://www.antillia.com/sol9.2.0/4.24.html">  <img src="http://www.antillia.com/sol9.2.0/images/SolFeatureDetector2.png" ></a>
<br>
<br>
Feature detection in a building image.<br>
<a href="http://www.antillia.com/sol9.2.0/4.24.html">  <img src="http://www.antillia.com/sol9.2.0/images/SolFeatureDetector3.png" ></a>

<br>
<!-- -->
<font size=2><a href="http://www.antillia.com/sol9.2.0/4.25.html" name="4.25">
<br>4.25 How to enumerate Video Input Devices to use in OpenCV VideoCapture? </a><br>
<br>
</b>
You can read a video image from a video input device somthing like a web-camera by using
<a href="http://docs.opencv.org/3.3.0/d8/dfe/classcv_1_1VideoCapture.html"> cv::VideoCapture</a> class of OpenCV. 
As you may know, however, OpenCV has no APIs to enumerate Video Input Devices.<br>
In Windows, you can get all video input devices informatiion by using COM interfaces 
of CLSID_SystemDeviceEnum, and CLSID_VideoInputDeviceCategory.<br>
In the latest SOL9 library, we have implemented VideoInputDeviceEnumerator and LabeledVideoDeviceComboBox classes to 
listup and select video devices.<br>
<br>
The following VideoDeviceEnumerator program is a simple example to select a video device from LabeledVideoDeviceComboBox,
and start to read a video image from the device.<br>
<br>
<a href="http://www.antillia.com/sol9.2.0/4.25.html">  <img src="http://www.antillia.com/sol9.2.0/images/VideoDeviceComboBox.png" ></a>
<br>
<br>
<a href="http://www.antillia.com/sol9.2.0/4.25.html">  <img src="http://www.antillia.com/sol9.2.0/images/VideoDeviceEnumerator.png" ></a>
<br>

<br>
<!-- -->
<font size=2><a href="http://www.antillia.com/sol9.2.0/4.26.html" name="4.26">
<br>4.26 How to map cv::Mat of OpenCV to a shape of OpenGL as a texture? </a><br>
<br>
Imagine to map a cv::Mat image of OpenCV to a shape of OpenGL as a texture by using an image method of OpenGLTexture2D class of SOL9. 
In the latest SOL9 library, we have implemented OpenGLImageInfo and OpenCVImageInfo classes to extract the raw image data from a cv::Mat.

The following OpenGLCVImageViews program is a simple example to display an OpenCVImageView and an OpenGLView side by side. 
In this example, we get an OpenGLImageInfo from the cv::Mat image displayed on the left pane by using OpenCVImageInfo class, and map the OpenGLImageInfo to a quad shape of OpenGL of the right pane ofas a texture.
of SOL9. 

<br>
<br>
<a href="http://www.antillia.com/sol9.2.0/4.26.html">  <img src="http://www.antillia.com/sol9.2.0/images/OpenGLCVImageViews.png" ></a>
<br>
<br>
<font size=2><a href="http://www.antillia.com/sol9.2.0/4.27.html" name="4.27">
<br>4.27 How to read a frame buffer of OpenGL and convert it to cv::Mat of OpenCV? </a><br>
<br>

<font size=2>
 Imagine to read pixel data of an OpenGL frame buffer and convert it to a cv::Mat image format of OpenCV.<br>
Reading pixel data of the frame buffer can be done by using <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glReadPixels.xml">glReadPixels</a> API of OpenGL, and creating a cv::Mat image 
by calling its constructor in the following way in a subclass, say SimpleGLView, derived from OpenGLView :<br>
<br>
</font>
<font size=2>
&nbsp;&nbsp;  class SimpleGLView :public OpenGLView {<br>
<br>
&nbsp;&nbsp;&nbsp;&nbsp;cv::Mat&nbsp;capture()<br>
&nbsp;&nbsp;&nbsp;&nbsp;{<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int&nbsp;w,&nbsp;h;<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;getSize(w,&nbsp;h);<br>
<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;w&nbsp;=&nbsp;(w/8)*8;<br>
<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;glReadBuffer(GL_FRONT);<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;glPixelStorei(GL_UNPACK_ALIGNMENT,&nbsp;1);<br>
<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;unsigned&nbsp;char*&nbsp;pixels&nbsp;=&nbsp;new&nbsp;unsigned&nbsp;char[3&nbsp;*&nbsp;w&nbsp;*&nbsp;h];<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;glReadPixels(0,&nbsp;0,&nbsp;w,&nbsp;h,&nbsp;GL_BGR,&nbsp;GL_UNSIGNED_BYTE,&nbsp;pixels);<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;return&nbsp;cv::Mat(h,&nbsp;w,&nbsp;CV_8UC3,&nbsp;pixels);<br>
&nbsp;&nbsp;&nbsp;&nbsp;}<br>
<br>
</font>
<font size=2>
The following BlurredMaterializedSpheres program is a simple example to display some materialized shperes on an OpenGLView and a blurred cv::Mat image 
,corresponding to the frame buffer of the OpenGLView, on an OpenCVImageView side by side. 

<br>
<br>
<a href="http://www.antillia.com/sol9.2.0/4.27.html">  
<img src= "http://www.antillia.com/sol9.2.0/images/BlurredMaterializedSpheres.png" ></a>
<br>
</font>
<br>
<br>
<font size=2><a href="http://www.antillia.com/sol9.2.0/4.28.html" name="4.28">
<br>4.28 How to transform an image by a dynamic color filter in OpenCV? </a><br>
<br>

<font size=2>
As you know, you can transform an image by using a cv::Mat filter(Kernel) and cv::transform API of OpenCV
as shown below.<br>
</font>
<br>

<font size=2>
&nbsp;&nbsp;&nbsp;&nbsp;void applySepiaFilter(const char* filename)<br>
&nbsp;&nbsp;&nbsp;&nbsp;{<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;cv::Mat originalImage = cv::imread(filename, cv::IMREAD_COLOR);<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;cv::Mat transformedImage = originalImage.clone();<br>
<br>    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;//sepia filter<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;cv::Mat sepia = (cv::Mat_&lt;float&gt;(3,3) &lt;&lt; <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;0.272, 0.534, 0.131,<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;0.349, 0.686, 0.168, <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;0.393, 0.769, 0.189); <br>
<bf>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;cv::transform(originalImage, sepia, transformedImage);<br>
&nbsp;&nbsp;&nbsp;&nbsp;  }<br>
</font>

<br>
<font>
In this case, the originalImage is transformed by the constant sepia filter to the transformedImage.
This is a traditional constant filter example, however, it is much better to be able to
 apply a dynamically changeable color filter (Kernel) to a cv::Mat image.<br>
<br>
The following ImageTransformationByDynamicColorFilter is a simple example to implement a dynamic color filter
by using OpenCVColorFilter class and ColorPositioner class of SOL9.<br>
<br>
</font>
<a href="http://www.antillia.com/sol9.2.0/4.28.html">  
<img src="http://www.antillia.com/sol9.2.0/images/ImageTransformationByDynamicColorFilter.png">
</a>
<br>


<br>
<br>
<font size=2><a href="http://www.antillia.com/sol9.2.0/4.29.html" name="4.29">
<br>4.29 How to render a textured sphere with Axis, Eye, and Light Positioner in OpenGL?</a><br>
<br>
 As show in <a href="http://www.antillia.com/sol9.2.0/4.19.html">4.19 How to render a textured sphere in OpenGL?</a>, it is easy to render and rotate a sphere textured by an image file in OpenGL.<br>
If we could dynamically change a rotation axis, an eye position, and a light position in that example, however, it would be a much better program.<br><br> 

The following TexturedSphereWithAxisEyeAndLightPositioner is a simple example to render a sphere textured by a cylindrical planet map.<br>

In this example, we have used Venus map 'ven0aaa2.jpg' Caltech/JPL/USGS in the page
<a href="https://maps.jpl.nasa.gov/venus.html">JPL NASA SOLAR SYSTEM SIMULATOR </a>.<br>
<br>
<a href="http://www.antillia.com/sol9.2.0/4.29.html"><img src="http://www.antillia.com/sol9.2.0/images/TexturedSphereWithAxisEyeLightPositioner_Venus.png"></a>
<br><br>
<font size=2>
We have also used the following Lunar Orbiter's 'Lunar_LO_UVVISv2_Hybrid_Mosaic_Global_1024.jpg' in the page
<a href="https://astropedia.astrogeology.usgs.gov/download/Moon/Lunar-Orbiter/thumbs/Lunar_LO_UVVISv2_Hybrid_Mosaic_Global_1024.jpg">Astrogeology Science Center</a>.
</font>
<br>
<br>
<a href="http://www.antillia.com/sol9.2.0/4.29.html">  <img src="http://www.antillia.com/sol9.2.0/images/TexturedSphereWithAxisEyeLightPositioner_LOMoon.png" ></a>

<br>
<br>
Furthermore, we have used the following Voyager Galileo IO 'jup1vss2.jpg' in the page 
<a href="https://maps.jpl.nasa.gov/jupiter.html">JPL NASA SOLAR SYSTEM SIMULATOR </a>
<br>
<br>
<a href="http://www.antillia.com/sol9.2.0/4.29.html">  <img src="http://www.antillia.com/sol9.2.0/images/TexturedSphereWithAxisEyeLightPositioner_IO.png" ></a>

<!-- -->
<br>
<br>
<font size=2><a href="http://www.antillia.com/sol9.2.0/4.30.html" name="4.30">
<br>4.30 How to detect a bounding box for an object in a cv::Mat of OpenCV?</a><br>
<br>
 As a simple application of OpenCV APIs, we consider to find  a bounding box for an object represented cv:Mat of OpenCV.
In this example, we do the following operations to find a bounding box.<br><br>
 
1. Apply cv::EdgePreseringFilter to originalImage of cv::Mat.<br><br>
2. Get a grayImage from the filterdImage.<br><br>
3. Apply cv::Canny Edge Detector to the grayImage.<br><br>
4. Find contours from the edgeDetectedImage.<br><br>
5. Get approximate polygonal coordinates from the contours.<br><br>
6. Get bounding rectangles from the contours polygonal coordinates.<br><br>
7. Find a single rectangle from the bounding rectanglese set.<br><br>

The following BoundingBoxDetector is a simple example to implement above operations to detect a single bounding box for an object in cv::Mat image.
<br><br>

<a href="http://www.antillia.com/sol9.2.0/4.30.html">  <img src="http://www.antillia.com/sol9.2.0/images/BoundingBoxDetector.png" ></a>
<br>
<br>
<a href="http://www.antillia.com/sol9.2.0/4.30.html">  <img src="http://www.antillia.com/sol9.2.0/images/BoundingBoxDetector4.png" ></a>
<!-- -->
<br>
<br>
<font size=2><a href="http://www.antillia.com/sol9.2.0/4.31.html" name="4.31">
<br>4.31 How to detect people in a cv::Mat image by using HOGDescriptor of OpenCV?</a><br>
<br>
  As you know, HOGDescriptor is an implementation of <a href ="https://docs.opencv.org/3.4.1/d5/d33/structcv_1_1HOGDescriptor.html">HOG (Histogram of Oriented Gradients) Descriptor</a> of OpenCV
and object detector.<br>
 HOGDescriptor supports two pre-trained people detector which can be returned by the following methods respectively:<br><br>
 
1. getDaimlerPeopleDetector()<br><br>
2. getDefaultPeopleDetector()<br><br>


The following HOGPeopleDetector is a simple example to detect people a in cv::Mat image by using above PeopleDetectors and a user-defined PeopleDetector.
<br><br>

<a href="http://www.antillia.com/sol9.2.0/4.31.html">  <img src="http://www.antillia.com/sol9.2.0/images/HOGPeopleDetector.png" ></a>
<br>
<br>
<a href="http://www.antillia.com/sol9.2.0/4.31.html">  <img src="http://www.antillia.com/sol9.2.0/images/HOGPeopleDetector2.png" ></a>

<br>
<br>

<!-- -->
<br>
<br>
<font size=2><a href="http://www.antillia.com/sol9.2.0/4.32.html" name="4.32">
<br>4.32 How to create CustomYoloObjectDetector class based on C APIs of darknet-master?</a><br>
<br>
  As you may know, you can use <b>Detector</b> C++ class in <i>yolo_v2_class.hpp</i> in include folder of <a href="https://github.com/AlexeyAB/darknet">darkent-master</a>
to detect objects in cv::Mat image as shown in the following example:<br><br>
<a href="http://www.antillia.com/sol9.2.0/sol9.2.0samples/yolov3/YoloObjectDetector.html">YoloObjectDetector</a>
<br><br>
 The Detector class is very simple to use, and very useful to get detailed information on the detected objects, provided you need not an image 
 which the bounding rectangles and names on the detected objects are not drawn.
<br><br>
 You can also create your own Detector C++ class by extending C APIs of dector.c, image.c, etc. in darknet_master/src folder.<br>  
The <a href="http://www.antillia.com/sol9.2.0/classes/Detector3.html">Detector3<a> is an example implementation  class, and  the following CustomYoloObjectDetector is a simple example to detect objects a in cv::Mat image by using the Detector3.
<br><br>

<a href="http://www.antillia.com/sol9.2.0/4.32.html">  <img src="http://www.antillia.com/sol9.2.0/sol9.2.0samples/yolov3/CustomYoloObjectDetector.png" ></a>
<br>
<br>
<a href="http://www.antillia.com/sol9.2.0/4.32.html">  <img src="http://www.antillia.com/sol9.2.0/sol9.2.0samples/yolov3/CustomYoloObjectDetector.2.png" ></a>

<br>
<br>

<!-- -->
<br>
<br>
<font size=2><a href="http://www.antillia.com/sol9.2.0/4.33.html" name="4.33">
<br>4.33 How to create DetectedObjectHTMLFileGenerator for YOLO by using SOL Detector3 and a template.html file ?</a><br>
<br>
It's much better to create an HTML file to display a detected-objects-image on a web browser than an interactive native UI program something like <a href="http://www.antillia.com/sol9.2.0/sol9.2.0samples/yolov3/CustomYoloObjectDetector.html">CustomYoloObjectDetector</a>.<br>
We have created an elementary command line program (DetectedObjectHTMLFileGenerator for YOLO) to generate such an HTML file from  a source image folder by using 
<a href="http://www.antillia.com/sol9.2.0/classes/Detector3.html">Detector3</a> C++ class and a <i>template.html</i> HTML file. <br>
<br>
The following web browser screen shot is a result of an example html file <i>detected.html</i> generated by the program.<br>

<br><br>

<a href="http://www.antillia.com/sol9.2.0/4.33.html">  <img src="http://www.antillia.com/sol9.2.0/sol9.2.0samples/yolov3/DetectedObjectHTMLFileGenerator.png" ></a>
<br>
<br>

<br>
<br>
<!-- bottom anchors end -->
<!--
<font size= 2 >
<hr noshade color = "lightgray">
<b>
Last modified: 8 Oct. 2017 
</b>
</font>
-->
<!-- Right End -->

<!--
================================================================================================
-->

</td>

</tr>
</table>

<font size = 2 color = "navy" >
<hr noshade color="navy">
&nbsp;<b>Last modified: 10 Feb. 2020</b>
</font>
<br>
<font color = "navy" size ="2">
<b>
Copyright (c) 2000-2020  Antillia.com ALL RIGHTS RESERVED. 
</b>
</font>
</div>

</body>
</html>




