ReMo
=====================================================

## Introduction

ReMo (Render Movie) is a generic SDK for procedural video synthesis tasks. This 
SDK allows developers and researchers to connect different source media (such as
common applications, WebCams, or even the whole desktop) to different target media 
(such as video files or internet video streams). ReMo is designed to be highly 
extensible, flexible, efficient and easy to integrate into different tools and 
frameworks.

## Dependencies
* Required dependencies:
    * FFmpeg/libAV
    * Threads

* Optional dependencies:
    * SDL
    * [WebStreamer](https://github.com/HBPVIS/webstreamer)
    * Poco (required if ReMo is build using WebStreamer: Foundation Net Zip JSON Util)

## Building

ReMo has been successfully built and used on Ubuntu 18.04/Debian Strech Stable. 
The following steps should be enough to build it just with the required dependencies. 
Nevertheless, to use the video streaming features, ReMo needs to be built with 
the WebStreamer dependency, and WebStreamer needs to be compiled as shared library. 
The WebStreamer build directory needs to be specified to ReMo at configuration time 
using CMAKE_PREFIX_PATH variable. The Poco framework is required if ReMo is compiled
using WebStreamer.

## Description

```bash
git clone https://github.com/gmrvvis/ReMo.git
mkdir ReMo/build && cd ReMo/build
cmake .. [-DCMAKE_PREFIX_PATH=/path/to/webstreamer/buildDirectory]
make
```
