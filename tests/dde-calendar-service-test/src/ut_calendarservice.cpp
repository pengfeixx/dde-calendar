/*
* Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
*
* Author:     hejinghai <hejinghai@uniontech.com>
*
* Maintainer: hejinghai <hejinghai@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ut_calendarservice.h"
#include "../third-party_stub/stub.h"
#include "config.h"
#include "../calendar-basicstruct/src/utils.h"
#include "src/scheduledatainfo.h"
#include <QSqlQuery>
#include <QDebug>

bool stub_OpenHuangliDatabase_service(void *obj, const QString &dbpath)
{
    Q_UNUSED(dbpath);
    HuangLiDataBase *o = reinterpret_cast<HuangLiDataBase *>(obj);
    QString name;
    {
        name = QSqlDatabase::database().connectionName();
    }
    o->m_database.removeDatabase(name);
    o->m_database = QSqlDatabase::addDatabase("QSQLITE");
    o->m_database.setDatabaseName(HL_DATABASE_DIR);
    return o->m_database.open();
}

void stub_OpenSchedulerDatabase_service(void *obj, const QString &dbpath)
{
    Q_UNUSED(dbpath);
    SchedulerDatabase *o = reinterpret_cast<SchedulerDatabase *>(obj);
    if (QSqlDatabase::contains("SchedulerDatabase")) {
        o->m_database = QSqlDatabase::database("SchedulerDatabase");
    } else {
        o->m_database = QSqlDatabase::addDatabase("QSQLITE", "SchedulerDatabase");
    }

    o->m_database.setDatabaseName(SD_DATABASE_DIR);
    o->m_database.open();
    if (o->m_database.isOpen()) {
        const QStringList tables = o->m_database.tables();
        if (tables.size() < 1) {
            o->CreateTables();
        } else {
            //初始化数据库表
            QSqlQuery query(o->m_database);
            //清空原始表
            QString strDeleteJobTable = "DROP TABLE jobs;";
            query.exec(strDeleteJobTable);
            if (query.isActive()) {
                query.finish();
            }

            QString strDeleteJobTypeTable = "DROP TABLE job_types;";
            query.exec(strDeleteJobTypeTable);
            if (query.isActive()) {
                query.finish();
            }

            //初始化本地job_types表，保证本地日历的可用性
            QDateTime currentDateTime = QDateTime::currentDateTime();
            QString sTime = Utils::toconvertData(currentDateTime);

            QString strInitJobType = QString("INSERT INTO job_types (created_at, updated_at, name, color) VALUES "
                                             "(\"%1\", \"%1\", \"学习\", \"#FF0000\"),"
                                             "(\"%1\", \"%1\", \"工作\", \"#00FF00\"),"
                                             "(\"%1\", \"%1\", \"其他\", \"#800080\");")
                                         .arg(sTime);
            query.exec(strInitJobType);
            if (query.isActive()) {
                query.finish();
            }

            o->m_database.commit();

            o->CreateTables();
        }
    }
}

ut_calendarservice::ut_calendarservice()
{
}

void ut_calendarservice::SetUp()
{
    Stub stub;
    stub.set(ADDR(HuangLiDataBase, OpenHuangliDatabase), stub_OpenHuangliDatabase_service);
    stub.set(ADDR(SchedulerDatabase, OpenSchedulerDatabase), stub_OpenSchedulerDatabase_service);
    service = new CalendarService();
}

void ut_calendarservice::TearDown()
{
    delete service;
    service = nullptr;
}

//QString CalendarService::GetFestivalMonth(quint32 year, quint32 month)
TEST_F(ut_calendarservice, GetFestivalMonth)
{
    const QString fesTenMonth = "[{\"description\":\"10月1日至10月8日放假8天，9月27日，10月10日上班\","
                                "\"id\":\"2020100110\",\"list\":[{\"date\":\"2020-10-1\",\"status\":1},"
                                "{\"date\":\"2020-10-2\",\"status\":1},"
                                "{\"date\":\"2020-10-3\",\"status\":1},"
                                "{\"date\":\"2020-10-4\",\"status\":1},"
                                "{\"date\":\"2020-10-5\",\"status\":1},"
                                "{\"date\":\"2020-10-6\",\"status\":1},"
                                "{\"date\":\"2020-10-7\",\"status\":1},"
                                "{\"date\":\"2020-10-8\",\"status\":1},"
                                "{\"date\":\"2020-9-27\",\"status\":2},"
                                "{\"date\":\"2020-10-10\",\"status\":2}],"
                                "\"month\":10,\"name\":\"中秋节\",\"rest\":\"10月9日至10月10日请假2天，与周末连休可拼11天长假。\"}]";
    QString festivalMonth = service->GetFestivalMonth(2020, 10);
    EXPECT_EQ(fesTenMonth, festivalMonth);
}

//QString CalendarService::GetHuangLiDay(quint32 year, quint32 month, quint32 day)
TEST_F(ut_calendarservice, GetHuangLiDay)
{
    //2020年12月13日黄历信息
    const QString huangli_20201213 = "{\"Avoid\":\"嫁娶.祈福.出火.移徙.入宅.\",\"GanZhiDay\":\"庚寅\",\"GanZhiMonth\":\"戊子\","
                                     "\"GanZhiYear\":\"庚子\",\"LunarDayName\":\"廿九\",\"LunarFestival\":\"\",\"LunarLeapMonth\":0,"
                                     "\"LunarMonthName\":\"十月\",\"SolarFestival\":\"南京大屠杀死难者国家公祭日\","
                                     "\"Suit\":\"纳财.开市.交易.立券.会亲友.进人口.经络.祭祀.祈福.安香.出火.求医.治病.修造.动土.拆卸.扫舍.安床."
                                     "栽种.牧养.开生坟.合寿木.入殓.安葬.启攒.\",\"Term\":\"\",\"Worktime\":0,\"Zodiac\":\"鼠\"}";
    quint32 year = 2020;
    quint32 month = 12;
    quint32 day = 13;
    QString gethuangli = service->GetHuangLiDay(year, month, day);
    EXPECT_EQ(huangli_20201213, gethuangli);

    //2020年12月14日黄历信息
    const QString huangli_20201214 = "{\"Avoid\":\"入宅.修造.动土.破土.安门.上梁.\",\"GanZhiDay\":\"辛卯\",\"GanZhiMonth\":\"戊子\","
                                     "\"GanZhiYear\":\"庚子\",\"LunarDayName\":\"三十\",\"LunarFestival\":\"\",\"LunarLeapMonth\":0,"
                                     "\"LunarMonthName\":\"十月\",\"SolarFestival\":\"\",\"Suit\":\"祭祀.入殓.移柩.余事勿取.\",\"Term\":"
                                     "\"\",\"Worktime\":0,\"Zodiac\":\"鼠\"}";
    day = 14;
    gethuangli = service->GetHuangLiDay(year, month, day);
    EXPECT_EQ(huangli_20201214, gethuangli);
}

//QString CalendarService::GetHuangLiMonth(quint32 year, quint32 month, bool fill)
TEST_F(ut_calendarservice, GetHuangLiMonth_01)
{
    QDate currentDate(2021, 1, 1);
    QDate testDate;
    QString fesMonth;
    for (int i = 0; i < 100; ++i) {
        testDate = currentDate.addMonths(i);
        fesMonth = service->GetHuangLiMonth(testDate.year(), testDate.month(), true);
        EXPECT_NE(fesMonth, "");
    }
}

TEST_F(ut_calendarservice, GetHuangLiMonth_02)
{
    QDate currentDate(2021, 1, 1);
    QDate testDate;
    QString fesMonth;
    for (int i = 0; i < 100; ++i) {
        testDate = currentDate.addMonths(i);
        fesMonth = service->GetHuangLiMonth(testDate.year(), testDate.month(), false);
        EXPECT_NE(fesMonth, "");
    }
}

//CaLunarDayInfo CalendarService::GetLunarInfoBySolar(quint32 year, quint32 month, quint32 day)
TEST_F(ut_calendarservice, GetLunarInfoBySolar)
{
    CaLunarDayInfo huangliDayInfo;

    QDate currentDate = QDate::currentDate();
    QDate testDate;
    QString fesMonth;
    for (int i = 0; i < 100; ++i) {
        testDate = currentDate.addDays(i);
        huangliDayInfo = service->GetLunarInfoBySolar(testDate.year(), testDate.month(), testDate.day());
        EXPECT_NE(huangliDayInfo.mGanZhiDay, "");
    }
}

//CaLunarMonthInfo CalendarService::GetLunarMonthCalendar(quint32 year, quint32 month, bool fill)
TEST_F(ut_calendarservice, GetLunarCalendarMonth_01)
{
    quint32 year = 2020;
    quint32 month = 12;
    bool fill = false;
    CaLunarMonthInfo monthInfo = service->GetLunarMonthCalendar(year, month, fill);
    EXPECT_NE(monthInfo.mCaLunarDayInfo.size(), 0);
}

TEST_F(ut_calendarservice, GetLunarCalendarMonth_02)
{
    quint32 year = 2020;
    quint32 month = 12;
    bool fill = true;
    CaLunarMonthInfo monthInfo = service->GetLunarMonthCalendar(year, month, fill);
    EXPECT_NE(monthInfo.mCaLunarDayInfo.size(), 0);
}

//QString CalendarService::GetType(qint64 id)
TEST_F(ut_calendarservice, GetType)
{
    //无type 0
    qint64 id = 0;
    QString type = service->GetType(id);
    EXPECT_EQ(type, "");

    id = 1;
    type = service->GetType(id);
    EXPECT_NE(type, "");
}

//qint64 CalendarService::CreateJob(const QString &jobInfo)
TEST_F(ut_calendarservice, CreateJob)
{
    QDateTime currentTime = QDateTime::currentDateTime();

    ScheduleDataInfo info;
    info.setTitleName("test ut");
    info.setType(1);
    info.setAllDay(false);
    info.setBeginDateTime(currentTime);
    info.setEndDateTime(currentTime.addSecs(60 * 60));

    qint64 intJob1 = service->CreateJob(ScheduleDataInfo::ScheduleToJsonStr(info));

    ScheduleDataInfo info_1;
    info_1.setTitleName("test ut1");
    info_1.setType(1);
    info_1.setAllDay(false);
    info_1.setBeginDateTime(currentTime.addSecs(60 * 60));
    info_1.setEndDateTime(currentTime.addSecs(60 * 60 * 2));

    qint64 intJob2 = service->CreateJob(ScheduleDataInfo::ScheduleToJsonStr(info_1));

    ScheduleDataInfo info_2;
    info_2.setTitleName("test ut2");
    info_2.setType(2);
    info_2.setAllDay(false);
    info_2.setBeginDateTime(currentTime.addSecs(60 * 60));
    info_2.setEndDateTime(currentTime.addSecs(60 * 60 * 2));

    qint64 intJob3 = service->CreateJob(ScheduleDataInfo::ScheduleToJsonStr(info_2));

    QString jobs1 = service->GetJob(intJob1);
    QString jobs2 = service->GetJob(intJob2);
    QString jobs3 = service->GetJob(intJob3);

    ScheduleDataInfo scheduleInfo1 = ScheduleDataInfo::JsonStrToSchedule(jobs1);
    EXPECT_TRUE(scheduleInfo1.getTitleName() == info.getTitleName());
    EXPECT_EQ(scheduleInfo1.getAllDay(), info.getAllDay());
    EXPECT_EQ(scheduleInfo1.getType(), info.getType());
    EXPECT_EQ(scheduleInfo1.getDescription(), info.getDescription());

    ScheduleDataInfo scheduleInfo2 = ScheduleDataInfo::JsonStrToSchedule(jobs2);
    EXPECT_TRUE(scheduleInfo2.getTitleName() == info_1.getTitleName());
    EXPECT_EQ(scheduleInfo2.getAllDay(), info_1.getAllDay());
    EXPECT_EQ(scheduleInfo2.getType(), info_1.getType());
    EXPECT_EQ(scheduleInfo2.getDescription(), info_1.getDescription());

    ScheduleDataInfo scheduleInfo3 = ScheduleDataInfo::JsonStrToSchedule(jobs3);
    EXPECT_TRUE(scheduleInfo3.getTitleName() == info_2.getTitleName());
    EXPECT_EQ(scheduleInfo3.getAllDay(), info_2.getAllDay());
    EXPECT_EQ(scheduleInfo3.getType(), info_2.getType());
    EXPECT_EQ(scheduleInfo3.getDescription(), info_2.getDescription());
}

//qint64 CalendarService::CreateType(const QString &typeInfo)
TEST_F(ut_calendarservice, CreateType)
{
    const QString typeInfo = "";
    service->CreateType(typeInfo);
}

//void CalendarService::DeleteJob(qint64 id)
TEST_F(ut_calendarservice, DeleteJob)
{
    QDateTime currentTime = QDateTime::currentDateTime();

    ScheduleDataInfo info;
    info.setTitleName("test ut");
    info.setType(1);
    info.setAllDay(false);
    info.setBeginDateTime(currentTime);
    info.setEndDateTime(currentTime.addSecs(60 * 60));

    qint64 intJob1 = service->CreateJob(ScheduleDataInfo::ScheduleToJsonStr(info));
    EXPECT_GT(intJob1, 0);
    service->DeleteJob(intJob1);
    EXPECT_EQ(service->GetJob(intJob1), "");
}

//void CalendarService::DeleteType(qint64 id)
TEST_F(ut_calendarservice, DeleteType)
{
    int id = 1;
    QString type = service->GetType(id);
    EXPECT_NE(type, "");
    service->DeleteType(id);
    type = service->GetType(id);
    EXPECT_NE(type, "");
}

//QString CalendarService::GetTypes()
TEST_F(ut_calendarservice, GetTypes)
{
    QString types_all = service->GetTypes();
    EXPECT_NE(types_all, "");
}

//QString CalendarService::GetJob(qint64 id)
TEST_F(ut_calendarservice, GetJob)
{
    QDateTime currentTime = QDateTime::currentDateTime();

    ScheduleDataInfo info;
    info.setTitleName("test ut");
    info.setType(1);
    info.setAllDay(false);
    info.setBeginDateTime(currentTime);
    info.setEndDateTime(currentTime.addSecs(60 * 60));

    qint64 intJob1 = service->CreateJob(ScheduleDataInfo::ScheduleToJsonStr(info));

    ScheduleDataInfo info_1;
    info_1.setTitleName("test ut1");
    info_1.setType(1);
    info_1.setAllDay(false);
    info_1.setBeginDateTime(currentTime.addSecs(60 * 60));
    info_1.setEndDateTime(currentTime.addSecs(60 * 60 * 2));

    qint64 intJob2 = service->CreateJob(ScheduleDataInfo::ScheduleToJsonStr(info_1));

    ScheduleDataInfo info_2;
    info_2.setTitleName("test ut2");
    info_2.setType(2);
    info_2.setAllDay(false);
    info_2.setBeginDateTime(currentTime.addSecs(60 * 60));
    info_2.setEndDateTime(currentTime.addSecs(60 * 60 * 2));

    qint64 intJob3 = service->CreateJob(ScheduleDataInfo::ScheduleToJsonStr(info_2));

    QString jobs1 = service->GetJob(intJob1);
    QString jobs2 = service->GetJob(intJob2);
    QString jobs3 = service->GetJob(intJob3);

    ScheduleDataInfo scheduleInfo1 = ScheduleDataInfo::JsonStrToSchedule(jobs1);
    EXPECT_TRUE(scheduleInfo1.getTitleName() == info.getTitleName());
    EXPECT_EQ(scheduleInfo1.getAllDay(), info.getAllDay());
    EXPECT_EQ(scheduleInfo1.getType(), info.getType());
    EXPECT_EQ(scheduleInfo1.getDescription(), info.getDescription());

    ScheduleDataInfo scheduleInfo2 = ScheduleDataInfo::JsonStrToSchedule(jobs2);
    EXPECT_TRUE(scheduleInfo2.getTitleName() == info_1.getTitleName());
    EXPECT_EQ(scheduleInfo2.getAllDay(), info_1.getAllDay());
    EXPECT_EQ(scheduleInfo2.getType(), info_1.getType());
    EXPECT_EQ(scheduleInfo2.getDescription(), info_1.getDescription());

    ScheduleDataInfo scheduleInfo3 = ScheduleDataInfo::JsonStrToSchedule(jobs3);
    EXPECT_TRUE(scheduleInfo3.getTitleName() == info_2.getTitleName());
    EXPECT_EQ(scheduleInfo3.getAllDay(), info_2.getAllDay());
    EXPECT_EQ(scheduleInfo3.getType(), info_2.getType());
    EXPECT_EQ(scheduleInfo3.getDescription(), info_2.getDescription());
}

//QString CalendarService::GetJobs(quint32 startYear, quint32 startMonth, quint32 startDay, quint32 endYear, quint32 endMonth, quint32 endDay)
TEST_F(ut_calendarservice, GetJobs)
{
    QDateTime currentTime = QDateTime::currentDateTime();

    ScheduleDataInfo info;
    info.setTitleName("test ut");
    info.setType(1);
    info.setAllDay(false);
    info.setBeginDateTime(currentTime);
    info.setEndDateTime(currentTime.addSecs(60 * 60));

    qint64 intJob1 = service->CreateJob(ScheduleDataInfo::ScheduleToJsonStr(info));
    EXPECT_GT(intJob1, 0);
    quint32 beginYear = static_cast<quint32>(info.getBeginDateTime().date().year());
    quint32 beginMonth = static_cast<quint32>(info.getBeginDateTime().date().month());
    quint32 beginDay = static_cast<quint32>(info.getBeginDateTime().date().day());
    quint32 endYear = static_cast<quint32>(info.getEndDateTime().date().year());
    quint32 endMonth = static_cast<quint32>(info.getEndDateTime().date().month());
    quint32 endDay = static_cast<quint32>(info.getEndDateTime().date().day());
    QString jobs = service->GetJobs(beginYear, beginMonth, beginDay, endYear, endMonth, endDay);
    QMap<QDate, QVector<ScheduleDataInfo>> infoMap = ScheduleDataInfo::StrJsonToRangeInfo(jobs);
    ASSERT_GT(infoMap.size(), 0);
    EXPECT_EQ(infoMap.begin().key(), currentTime.date());
    ASSERT_GT(infoMap.begin().value().size(), 0);
    EXPECT_EQ(infoMap.begin().value().at(0).getTitleName(), info.getTitleName());
}

//QString CalendarService::QueryJobs(const QString &params);
TEST_F(ut_calendarservice, QueryJobs)
{
    QDateTime currentTime = QDateTime::currentDateTime();

    ScheduleDataInfo info;
    info.setTitleName("test ut");
    info.setType(1);
    info.setAllDay(false);
    info.setBeginDateTime(currentTime);
    info.setEndDateTime(currentTime.addSecs(60 * 60));

    qint64 intJob1 = service->CreateJob(ScheduleDataInfo::ScheduleToJsonStr(info));
    EXPECT_GT(intJob1, 0);

    const QString params = QString("{\"key\":\"%1\",\"Start\":\"%2\",\"End\":\"%2\"}").arg("").arg(info.getBeginDateTime().toString("yyyy-MM-ddTHH:mm:ss")).arg(info.getEndDateTime().toString("yyyy-MM-ddTHH:mm:ss"));
    QString qJobs = service->QueryJobs(params);
    QMap<QDate, QVector<ScheduleDataInfo>> infoMap = ScheduleDataInfo::StrJsonToRangeInfo(qJobs);
    ASSERT_GT(infoMap.size(), 0);
    EXPECT_EQ(infoMap.begin().key(), currentTime.date());
    ASSERT_GT(infoMap.begin().value().size(), 0);
    EXPECT_EQ(infoMap.begin().value().at(0).getTitleName(), info.getTitleName());
}

//void CalendarService::UpdateJob(const QString &jobInfo);
TEST_F(ut_calendarservice, UpdateJob)
{
    QDateTime currentTime = QDateTime::currentDateTime();

    ScheduleDataInfo info;
    info.setTitleName("test ut");
    info.setType(1);
    info.setAllDay(false);
    info.setBeginDateTime(currentTime);
    info.setEndDateTime(currentTime.addSecs(60 * 60));

    qint64 intJob1 = service->CreateJob(ScheduleDataInfo::ScheduleToJsonStr(info));
    EXPECT_GT(intJob1, 0);

    QString getInfoStr = service->GetJob(intJob1);
    ScheduleDataInfo getInfo = ScheduleDataInfo::JsonStrToSchedule(getInfoStr);
    getInfo.setTitleName("test update");
    service->UpdateJob(ScheduleDataInfo::ScheduleToJsonStr(getInfo));
    QString getChangetInfoStr = service->GetJob(intJob1);
    ScheduleDataInfo changetInfo = ScheduleDataInfo::JsonStrToSchedule(getChangetInfoStr);
    EXPECT_EQ(changetInfo.getTitleName(), getInfo.getTitleName());
}

//QString CalendarService::QueryJobsWithLimit(const QString &params, qint32 maxNum);
TEST_F(ut_calendarservice, QueryJobsWithLimit)
{
    QDateTime currentTime = QDateTime::currentDateTime();

    ScheduleDataInfo info;
    info.setTitleName("test ut");
    info.setType(1);
    info.setAllDay(false);
    info.setBeginDateTime(currentTime);
    info.setEndDateTime(currentTime.addSecs(60 * 60));

    qint64 intJob1 = service->CreateJob(ScheduleDataInfo::ScheduleToJsonStr(info));
    EXPECT_GT(intJob1, 0);
    const QString params = QString("{\"key\":\"%1\",\"Start\":\"%2\",\"End\":\"%3\"}").arg("").arg(info.getBeginDateTime().toString("yyyy-MM-ddTHH:mm:ss")).arg(info.getEndDateTime().toString("yyyy-MM-ddTHH:mm:ss"));
    QString qJobs = service->QueryJobsWithLimit(params, 1);
    QMap<QDate, QVector<ScheduleDataInfo>> infoMap = ScheduleDataInfo::StrJsonToRangeInfo(qJobs);
    ASSERT_GT(infoMap.size(), 0);
    EXPECT_EQ(infoMap.begin().key(), currentTime.date());
    ASSERT_GT(infoMap.begin().value().size(), 0);
    EXPECT_EQ(infoMap.begin().value().at(0).getTitleName(), info.getTitleName());
}

//QString CalendarService::QueryJobsWithRule(const QString &params, const QString &rules);
TEST_F(ut_calendarservice, QueryJobsWithRule)
{
    QDateTime currentTime = QDateTime::currentDateTime();

    ScheduleDataInfo info;
    info.setTitleName("test ut");
    info.setType(1);
    info.setAllDay(false);
    info.setBeginDateTime(currentTime);
    info.setEndDateTime(currentTime.addSecs(60 * 60));

    qint64 intJob1 = service->CreateJob(ScheduleDataInfo::ScheduleToJsonStr(info));
    EXPECT_GT(intJob1, 0);
    const QString params = QString("{\"key\":\"%1\",\"Start\":\"%2\",\"End\":\"%3\"}").arg("").arg(info.getBeginDateTime().toString("yyyy-MM-ddTHH:mm:ss")).arg(info.getEndDateTime().toString("yyyy-MM-ddTHH:mm:ss"));
    const QString rules = "FREQ=DAILY;BYDAY=MO,TU,WE,TH,FR;COUNT=2";
    QString qJobs = service->QueryJobsWithRule(params, rules);
    QMap<QDate, QVector<ScheduleDataInfo>> infoMap = ScheduleDataInfo::StrJsonToRangeInfo(qJobs);
    ASSERT_EQ(infoMap.size(), 0);
}

//void CalendarService::UpdateType(const QString &typeInfo)
TEST_F(ut_calendarservice, UpdateType)
{
    int id = 1;
    QString getType = service->GetType(id);
    QString updateTypeJson = QString("{\"ID\":%1,\"Name\":\"test\",\"Color\":\"#CC99AA\"}").arg(id);
    service->UpdateType(updateTypeJson);
    EXPECT_EQ(getType, service->GetType(id));
}
