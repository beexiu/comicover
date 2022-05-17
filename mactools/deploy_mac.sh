#!/bin/bash

basepath=$(cd `dirname $0`; pwd)
cd ${basepath}/../output/build-comicover-Qt_6_2_4_for_macOS-Release
/Users/zhenggeng/Qt/6.2.4/macos/bin/macdeployqt comicover.app

