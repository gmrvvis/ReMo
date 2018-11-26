/*
 * Copyright (c) 2018 CCS/UPM - GMRV/URJC.
 *
 * Authors: Juan Pedro Brito Méndez <juanpedro.brito@upm.es>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef REMO_DEFSFFMPEG_H
#define REMO_DEFSFFMPEG_H

#include <string>
#include <iostream>

#define __STDC_CONSTANT_MACROS

#ifdef __cplusplus
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavcodec/avfft.h>
#include <libavdevice/avdevice.h>

//lib av formtar
#include <libavformat/avformat.h>
#include <libavformat/avio.h>

//lib avfilter
#include <libavfilter/avfilter.h>
#include <libavfilter/buffersink.h>
#include <libavfilter/buffersrc.h>

//lib avutil
#include <libavutil/opt.h>
#include <libavutil/common.h>
#include <libavutil/channel_layout.h>
#include <libavutil/imgutils.h>
#include <libavutil/mathematics.h>
#include <libavutil/samplefmt.h>
#include <libavutil/time.h>
#include <libavutil/opt.h>
#include <libavutil/pixdesc.h>
#include <libavutil/file.h>

//lib swscale
#include <libswscale/swscale.h>

};
#endif //cpp

#endif //REMO_DEFSFFMPEG_H
