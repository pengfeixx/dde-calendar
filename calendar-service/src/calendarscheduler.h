/*
* Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
*
* Author:     kongyunzhen <kongyunzhen@uniontech.com>
*
* Maintainer: kongyunzhen <kongyunzhen@uniontech.com>
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
#ifndef CALENDARSCHEDULER_H
#define CALENDARSCHEDULER_H
#include "dbmanager/schedulerdatabase.h"
#include "src/scheduledatainfo.h"

#include <QObject>
#include <QMutex>

class JobRemindManager;
class QTimer;

class CalendarScheduler : public QObject
{
    Q_OBJECT
public:
    explicit CalendarScheduler(QObject *parent = nullptr);
    ~CalendarScheduler();

    QString GetType(qint64 id);
    QString GetTypes();
    void DeleteJob(qint64 id);
    void DeleteType(qint64 id);
    QString GetJob(qint64 id);
    qint64 CreateJob(const QString &jobInfo);
    void UpdateJob(const QString &jobInfo);
    void UpdateType(const QString &typeInfo);
    QString GetJobs(const QDateTime &start, const QDateTime &end);
    QString QueryJobs(const QString &params);
    QString QueryJobsWithLimit(const QString &params, qint32 maxNum);
    QString QueryJobsWithRule(const QString &params, const QString &rules);

    //CalendarScheduler: jobtype & color
    /**
     * @brief CreateJobType    创建日程类型
     * param  jobTypeInfo      json格式的日程类型信息
     * return bool             返回操作结果
     */
    bool CreateJobType(const QString &jobTypeInfo);//
    /**
     * @brief DeleteJobType    删除日程类型
     * param  typeNo           日程类型编号
     * return bool             返回操作结果
     */
    bool DeleteJobType(const int &typeNo);
    /**
     * @brief UpdateJobType    更新日程类型
     * param  jobTypeInfo      json格式的日程类型信息
     * return bool             返回操作结果
     */
    bool UpdateJobType(const QString &jobTypeInfo);
    /**
     * @brief GetJobTypeList   获取日程类型字符串
     * return bool             返回查询结果
     */
    QString GetJobTypeList();
    /**
     * @brief CreateColorType  创建颜色类型
     * param  colorTypeInfo    json格式的颜色类型信息
     * return bool             返回操作结果
     */
    bool CreateColorType(const QString &colorTypeInfo);
    /**
     * @brief DeleteColorType  删除颜色类型
     * param  typeNo           颜色类型编号
     * return bool             返回操作结果
     */
    bool DeleteColorType(const int &typeNo);
    /**
     * @brief UpdateColorType  更新日程类型
     * param  colorTypeInfo    json格式的颜色类型信息
     * return bool             返回操作结果
     */
    bool UpdateColorType(const QString &colorTypeInfo);
    /**
     * @brief GetColorTypeList 获取日程类型字符串
     * return bool             返回查询结果
     */
    QString GetColorTypeList();

    void remindJob(const qint64 id, const qint64 recurID);

    /**
     * @brief UpdateRemindTimeout       更新未来10分钟有提醒信息的日程
     * @param isClear                   是否清空日程定时任务数据库
     */
    void UpdateRemindTimeout(bool isClear);

    /**
     * @brief notifyMsgHanding      处理通知弹框信息
     * @param jobID                 日程ID
     * @param recurID               重复日程编号
     * @param operationNum          操作编号
     */
    void notifyMsgHanding(const qint64 jobID, const qint64 recurID, const int operationNum);

private:
    void initConnections();
    static quint32 GetFestivalId(const QString &name);
    void IsFestivalJobEnabled();
    QList<stJobArr> GetJobsBetween(const QDateTime &start, const QDateTime &end, const QList<Job> &joblist, bool needFestival, const QString &querykey = QString(), bool bextend = true);
    QList<stJobTime> GetJobTimesBetween(const QDateTime &start, const QDateTime &end, const Job &job);
    void FillFestivalJobs(const QDateTime &start, const QDateTime &end, const QString &querykey, QList<stJobArr> &listjob);
    QList<QDateTime> GetIgnoreList(const Job &job);
    bool ContainsInIgnoreList(const QList<QDateTime> &ignorelist, const QDateTime &time);
    bool OverLap(const QDateTime &start, const QDateTime &end, const QDateTime &jobstart, const QDateTime &jobend);
    QDateTime GetNextJobStartTimeByRule(const stRRuleOptions &options, const QDateTime &datetime);
    stRRuleOptions ParseRRule(const QString &rule);
    QString JobArrListToJsonStr(const QList<stJobArr> &jobArrList);
    QList<Job> GetRemindJobs(const QDateTime &start, const QDateTime &end);
    QDateTime GetJobRemindTime(const Job &job);
    QDateTime ParseRemind(const QDateTime &tm, const QString &strremind);
    void AfterJobChanged(const QList<qlonglong> &Ids);
    QList<stJobArr> FilterDateJobsWrap(const QList<stJobArr> &arrList, const QDateTime &start, const QDateTime &end);

    Job josnStringToJob(const QString &str);

    /**
     * @brief getRemindTimeByCount 获取下次提醒时间
     * @param count 第几次提醒，从1开始
     * @return
     */
    QDateTime getRemindTimeByCount(int count);

    /**
     * @brief getRemindTimeByMesc 获取下次提醒时间
     * @param duration 毫秒时长
     * @return
     */
    QDateTime getRemindTimeByMesc(qint64 duration);

signals:
    void NotifyJobChange(const QList<Job> &jobs);
    void NotifyUpdateRemindJobs(const QList<Job> &jobs);
    void JobsUpdated(const QList<qlonglong> &Ids);
    //日程类型发生改变
    void JobTypeOrColorUpdated();
    void signalRemindJob(const Job &job);
    void signalNotifyMsgHanding(const Job &job, const int operationNum);
    void signalCloseNotification(quint32 notifyID);

private slots:

    void OnModifyJobRemind(const Job &job, const QString &remind);
    void saveNotifyID(const Job &job, int notifyid);

private:
    SchedulerDatabase *m_database;
    JobRemindManager *m_jobremindmanager;
    bool m_festivalJobEnabled = false; //是否允许节假日日程
    static QMap<QString, quint32> m_festivalIdMap; //节日对应节日Id
    static quint32 nextFestivalJobId; //下一个节日id
    static QMutex m_getJobIdMutex; //节日id获取锁
    QThread *threadremind = nullptr;
};

#endif // CALENDARSCHEDULER_H
