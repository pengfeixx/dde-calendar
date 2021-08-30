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

#include "ut_schedulerdatabase.h"
#include "calendarscheduler.h"
#include "../../calendar-basicstruct/src/utils.h"
#include "../third-party_stub/stub.h"

#include "src/scheduledatainfo.h"

#include "config.h"
#include <QSqlQuery>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>

QString writableLocation_Stub(QStandardPaths::StandardLocation type)
{
    Q_UNUSED(type)
    return QDir::currentPath();
}

//OpenSchedulerDatabase
void stub_OpenSchedulerDatabase(void *obj, const QString &dbpath)
{
    Q_UNUSED(dbpath);
    SchedulerDatabase *o = reinterpret_cast<SchedulerDatabase *>(obj);
    QString name;
    {
        name = QSqlDatabase::database().connectionName();
    }
    o->m_database.removeDatabase(name);
    o->m_database = QSqlDatabase::addDatabase("QSQLITE");
    o->m_database.setDatabaseName(SD_DATABASE_DIR);
    o->m_database.open();
    if (o->m_database.isOpen()) {
        const QStringList tables = o->m_database.tables();
        if (tables.size() < 1) {
            o->CreateTables();
        } else {
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

ut_schedulerdatabase::ut_schedulerdatabase()
{
}

void ut_schedulerdatabase::SetUp()
{
    Stub stub;
    stub.set(ADDR(SchedulerDatabase, OpenSchedulerDatabase), stub_OpenSchedulerDatabase);
    sDb = new SchedulerDatabase();
    qRegisterMetaType<Job>("Job");
    qRegisterMetaType<QList<Job>>("QList<Job>");
}

void ut_schedulerdatabase::TearDown()
{
    delete sDb;
    sDb = nullptr;
}

//qint64 SchedulerDatabase::CreateJob(const Job &job)
TEST_F(ut_schedulerdatabase, CreateJob)
{
    //创建多个日程进行测试
    Job job1;
    job1.Start = QDateTime::fromString("2020-12-05T00:00:00+08:00", Qt::ISODate);
    job1.End = QDateTime::fromString("2020-12-05T23:59:00+08:00", Qt::ISODate);
    job1.AllDay = true;
    job1.Type = 1;
    job1.Description = "";
    job1.ID = 0;
    job1.Ignore = "[]";
    job1.Title = "UT测试A";
    job1.RRule = "FREQ=DAILY;BYDAY=MO,TU,WE,TH,FR;COUNT=3";
    job1.RecurID = 0;
    job1.Remind = "1;09:00";

    qint64 intJob1 = sDb->CreateJob(job1);

    Job job2;
    job2.Start = QDateTime::fromString("2020-12-09T00:00:00+08:00", Qt::ISODate);
    job2.End = QDateTime::fromString("2020-12-09T23:59:00+08:00", Qt::ISODate);
    job2.AllDay = true;
    job2.Type = 1;
    job2.Description = "";
    job2.ID = 0;
    job2.Ignore = "[\"2020-12-11T00:00:00+08:00\"]";
    job2.Title = "UT测试B";
    job2.RRule = "FREQ=DAILY;BYDAY=MO,TU,WE,TH,FR;COUNT=2";
    job2.RecurID = 0;
    job2.Remind = "1;09:00";
    qint64 intJob2 = sDb->CreateJob(job2);

    //为delete提供待删除数据
    Job job3;
    job3.Start = QDateTime::fromString("2020-12-14T00:00:00+08:00", Qt::ISODate);
    job3.End = QDateTime::fromString("2020-12-14T23:59:00+08:00", Qt::ISODate);
    job3.AllDay = true;
    job3.Type = 1;
    job3.Description = "";
    job3.ID = 0;
    job3.Ignore = "[]";
    job3.Title = "UT测试C";
    job3.RRule = "FREQ=DAILY;BYDAY=MO,TU,WE,TH,FR;COUNT=4";
    job3.RecurID = 0;
    job3.Remind = "1;09:00";
    //根据创建日程获取到的日程id获取对应的日程
    qint64 intJob3 = sDb->CreateJob(job3);
    QString jobs1 = sDb->GetJob(intJob1);
    QString jobs2 = sDb->GetJob(intJob2);
    QString jobs3 = sDb->GetJob(intJob3);
    //将获取到的日程和创建的日程作对比
    ScheduleDataInfo scheduleInfo1 = ScheduleDataInfo::JsonStrToSchedule(jobs1);
    EXPECT_TRUE(scheduleInfo1.getTitleName() == job1.Title);
    EXPECT_EQ(scheduleInfo1.getAllDay(), job1.AllDay);
    EXPECT_EQ(scheduleInfo1.getType(), job1.Type);
    EXPECT_EQ(scheduleInfo1.getDescription(), job1.Description);

    ScheduleDataInfo scheduleInfo2 = ScheduleDataInfo::JsonStrToSchedule(jobs2);
    EXPECT_TRUE(scheduleInfo2.getTitleName() == job2.Title);
    EXPECT_EQ(scheduleInfo2.getAllDay(), job2.AllDay);
    EXPECT_EQ(scheduleInfo2.getType(), job2.Type);
    EXPECT_EQ(scheduleInfo2.getDescription(), job2.Description);

    ScheduleDataInfo scheduleInfo3 = ScheduleDataInfo::JsonStrToSchedule(jobs3);
    EXPECT_TRUE(scheduleInfo3.getTitleName() == job3.Title);
    EXPECT_EQ(scheduleInfo3.getAllDay(), job3.AllDay);
    EXPECT_EQ(scheduleInfo3.getType(), job3.Type);
    EXPECT_EQ(scheduleInfo3.getDescription(), job3.Description);
}


TEST_F(ut_schedulerdatabase, GetAllOriginJobs)
{
    Job job1;
    job1.Start = QDateTime::fromString("2020-12-05T00:00:00+08:00", Qt::ISODate);
    job1.End = QDateTime::fromString("2020-12-05T23:59:00+08:00", Qt::ISODate);
    job1.AllDay = true;
    job1.Type = 1;
    job1.Description = "";
    job1.ID = 0;
    job1.Ignore = "[]";
    job1.Title = "UT测试A";
    job1.RRule = "FREQ=DAILY;BYDAY=MO,TU,WE,TH,FR;COUNT=3";
    job1.RecurID = 0;
    job1.Remind = "1;09:00";

    qint64 intJob1 = sDb->CreateJob(job1);
    EXPECT_GT(intJob1, 0);

    QList<Job> jobList = sDb->GetAllOriginJobs();
    ASSERT_EQ(jobList.size(), 1) << "获取到的jobList" << jobList.size();
    EXPECT_EQ(jobList.at(0).Title, job1.Title);

    QList<Job> jobListP = sDb->GetAllOriginJobs("", "");
    EXPECT_EQ(jobList.size(), 1);
    EXPECT_EQ(jobList.at(0).Title, job1.Title);

    QList<Job> jobListttt = sDb->GetAllOriginJobs("ttt", "");
    EXPECT_EQ(jobListttt.size(), 0);
}

////QList<Job> SchedulerDatabase::GetAllOriginJobsWithRule(const QString &key, const QString &rules)
TEST_F(ut_schedulerdatabase, GetAllOriginJobsWithRule)
{
    Job job1;
    job1.Start = QDateTime::fromString("2020-12-05T00:00:00+08:00", Qt::ISODate);
    job1.End = QDateTime::fromString("2020-12-05T23:59:00+08:00", Qt::ISODate);
    job1.AllDay = true;
    job1.Type = 1;
    job1.Description = "";
    job1.ID = 0;
    job1.Ignore = "[]";
    job1.Title = "UT测试A";
    job1.RRule = "FREQ=DAILY;BYDAY=MO,TU,WE,TH,FR;COUNT=3";
    job1.RecurID = 0;
    job1.Remind = "1;09:00";

    qint64 intJob1 = sDb->CreateJob(job1);
    EXPECT_GT(intJob1, 0);

    QList<Job> jobs = sDb->GetAllOriginJobsWithRule("key", "rules");
    EXPECT_EQ(jobs.size(), 0);

    QList<Job> jobs1 = sDb->GetAllOriginJobsWithRule("UT测试A", "rules");
    EXPECT_EQ(jobs1.size(), 0);

    QList<Job> jobs2 = sDb->GetAllOriginJobsWithRule("", "BYDAY=MO,TU,WE,TH,FR");
    EXPECT_EQ(jobs2.size(), 1);

    QList<Job> jobs3 = sDb->GetAllOriginJobsWithRule("UT测试A", "BYDAY=MO,TU,WE,TH,FR");
    EXPECT_EQ(jobs3.size(), 1);
}

////QList<Job> SchedulerDatabase::GetJobsContainRemind()
TEST_F(ut_schedulerdatabase, GetJobsContainRemind)
{
    QList<Job> jobList = sDb->GetJobsContainRemind();
    EXPECT_EQ(jobList.size(), 0);

    Job job1;
    job1.Start = QDateTime::fromString("2020-12-05T00:00:00+08:00", Qt::ISODate);
    job1.End = QDateTime::fromString("2020-12-05T23:59:00+08:00", Qt::ISODate);
    job1.AllDay = true;
    job1.Type = 1;
    job1.Description = "";
    job1.ID = 0;
    job1.Ignore = "[]";
    job1.Title = "UT测试A";
    job1.RRule = "FREQ=DAILY;BYDAY=MO,TU,WE,TH,FR;COUNT=3";
    job1.RecurID = 0;
    job1.Remind = "1;09:00";

    qint64 intJob1 = sDb->CreateJob(job1);
    EXPECT_GT(intJob1, 0);

    QList<Job> jobList1 = sDb->GetJobsContainRemind();
    EXPECT_EQ(jobList1.size(), 1);
}

////void SchedulerDatabase::DeleteJob(qint64 id)
TEST_F(ut_schedulerdatabase, DeleteJob)
{
    Job job1;
    job1.Start = QDateTime::fromString("2020-12-05T00:00:00+08:00", Qt::ISODate);
    job1.End = QDateTime::fromString("2020-12-05T23:59:00+08:00", Qt::ISODate);
    job1.AllDay = true;
    job1.Type = 1;
    job1.Description = "";
    job1.ID = 0;
    job1.Ignore = "[]";
    job1.Title = "UT测试A";
    job1.RRule = "FREQ=DAILY;BYDAY=MO,TU,WE,TH,FR;COUNT=3";
    job1.RecurID = 0;
    job1.Remind = "1;09:00";

    qint64 intJob1 = sDb->CreateJob(job1);
    EXPECT_GT(intJob1, 0);
    QString jobstr = sDb->GetJob(intJob1);
    EXPECT_NE(jobstr, "");
    sDb->DeleteJob(intJob1);
    QString jobstr1 = sDb->GetJob(intJob1);
    EXPECT_EQ(jobstr1, "");
}

////qint64 SchedulerDatabase::UpdateJob(const QString &jobInfo)
TEST_F(ut_schedulerdatabase, UpdateJob)
{
    QDateTime currentTime = QDateTime::currentDateTime();

    ScheduleDataInfo info;
    info.setTitleName("test ut");
    info.setType(1);
    info.setAllDay(false);
    info.setBeginDateTime(currentTime);
    info.setEndDateTime(currentTime.addSecs(60 * 60));

    Job job;
    job.Title = info.getTitleName();
    job.Type = info.getType();
    job.AllDay = info.getAllDay();
    job.Start = info.getBeginDateTime();
    job.End = info.getEndDateTime();

    int jobid = static_cast<int>(sDb->CreateJob(job));
    EXPECT_GT(jobid, 0);
    info.setID(jobid);

    info.setTitleName("change title");
    qint64 updateid = sDb->UpdateJob(info.ScheduleToJsonStr(info));
    EXPECT_NE(updateid, -1);
    EXPECT_EQ(jobid, updateid);

    ScheduleDataInfo changeInfo = ScheduleDataInfo::JsonStrToSchedule(sDb->GetJob(updateid));
    EXPECT_EQ(changeInfo, info);
}

////bool SchedulerDatabase::UpdateJobIgnore(const QString &strignore, qint64 id)
TEST_F(ut_schedulerdatabase, UpdateJobIgnore)
{
    const QString strignore = "[\"2020-12-07T00:00:00+08:00\"]";

    Job job1;
    job1.Start = QDateTime::fromString("2020-12-05T00:00:00+08:00", Qt::ISODate);
    job1.End = QDateTime::fromString("2020-12-05T23:59:00+08:00", Qt::ISODate);
    job1.AllDay = true;
    job1.Type = 1;
    job1.Description = "";
    job1.ID = 0;
    job1.Ignore = "[\"2020-12-08T00:00:00+08:00\"]";
    job1.Title = "UT测试A";
    job1.RRule = "FREQ=DAILY;BYDAY=MO,TU,WE,TH,FR;COUNT=6";
    job1.RecurID = 0;
    job1.Remind = "1;09:00";

    qint64 intJob1 = sDb->CreateJob(job1);
    EXPECT_GT(intJob1, 0);

    bool updateIgnore = sDb->UpdateJobIgnore(strignore, intJob1);
    EXPECT_FALSE(updateIgnore) << "job id:" << intJob1;
}

////void SchedulerDatabase::UpdateType(const QString &typeInfo)
TEST_F(ut_schedulerdatabase, Typehandle)
{
    QString updateTypeJson = "{\"ID\":1,\"Name\":\"嗨皮\",\"Color\":\"#CC99AA\"}";
    sDb->UpdateType(updateTypeJson);
    sDb->DeleteType(1);
}
