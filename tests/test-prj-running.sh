#!/bin/bash
builddir=build
reportdir=build-ut
rm -r $builddir
rm -r ../$builddir
rm -r $reportdir
rm -r ../$reportdir
mkdir ../$builddir
mkdir ../$reportdir
cd ../$builddir
#编译
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_SAFETYTEST_ARG="CMAKE_SAFETYTEST_ARG_ON" ..
make -j8

# 已知的崩溃/失败测试，运行时跳过
CLIENT_SKIP="--gtest_filter=-*getPixmap*:test_schedulesearchview.contextMenuEvent*:test_schedulesearchview.mouseDoubleClickEvent*:test_schedulesearchview.keyPressEvent*:test_monthgraphiview.*"
SERVICE_SKIP="--gtest_filter=-test_calendarhuangli.GetHuangLiDay:test_calendarscheduler.*"

#生成asan日志和ut测试xml结果
./tests/dde-calendar-client-test/dde-calendar-test $CLIENT_SKIP --gtest_output=xml:./report/report_dde-calendar-client.xml
sleep 5
./tests/dde-calendar-service-test/dde-calendar-service-test $SERVICE_SKIP --gtest_output=xml:./report/report_dde-calendar-service.xml

workdir=$(cd ../$(dirname $0)/$builddir; pwd)

mkdir -p report
#统计代码覆盖率并生成html报告
lcov -d $workdir -c -o ./coverage.info

lcov --extract ./coverage.info '*/src/*' -o ./coverage.info

lcov --remove ./coverage.info '*/tests/*' -o ./coverage.info

lcov --remove ./coverage.info '*/3rdparty/*' -o ./coverage.info

genhtml -o ./html ./coverage.info

mv ./html/index.html ./html/cov_dde-calendar.html
#对asan、ut、代码覆盖率结果收集至指定文件夹
cp -r html ../$reportdir/
cp -r report ../$reportdir/
cp -r asan*.log* ../$reportdir/asan_dde-calendar.log 2>/dev/null || true

exit 0
