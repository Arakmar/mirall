#ifndef SYNCWINDOW_H
#define SYNCWINDOW_H

#include <QMainWindow>
#include "QWebDAV.h"
#include <QSqlDatabase>
#include <QQueue>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QSet>

class QTimer;
class OwnCloudSync;
class QSignalMapper;

namespace Ui {
    class SyncWindow;
}

class SyncWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SyncWindow(QWidget *parent = 0);
    ~SyncWindow();

private:
    Ui::SyncWindow *ui;
    QSystemTrayIcon *mSystemTray;
    QList<OwnCloudSync*> mAccounts;
    OwnCloudSync *mCurrentAccountEdit;
    QStringList mAccountNames;
    qint64 mTotalSyncs;
    bool mBusy;
    int mCurrentAccount;
    int mEditingConfig;
    qint64 mTotalToDownload;
    qint64 mTotalToUpload;
    qint64 mTotalToTransfer;
    qint64 mTotalTransfered;
    qint64 mTotalDownloaded;
    qint64 mTotalUploaded;
    qint64 mCurrentFileSize;
    QString mCurrentFile;
    QString mTransferState;
    bool mConflictsExist;
    QString mConfigDirectory;
    QSignalMapper *mAccountsSignalMapper;
    QQueue<OwnCloudSync*> mAccountsReadyToSync;

    QIcon mDefaultIcon;
    QIcon mSyncIcon;
    QIcon mDefaultConflictIcon;
    QIcon mSyncConflictIcon;

    void processNextStep();
    void saveLogs();
    void rebuildAccountsTable();
    OwnCloudSync* addAccount(QString name);
    OwnCloudSync* getAccount(QString name);
    void accountEnabledChanged(int row);
    void editConfig(int row);

public slots:
    //void timeToSync();
    void updateStatus();
    void transferProgress(qint64 current,qint64 total);
    void systemTrayActivated(QSystemTrayIcon::ActivationReason reason);
    void closeEvent(QCloseEvent *event);

    void slotAccountsSignalMapper(int row);

    // GUI related slots
    void on_buttonSave_clicked();
    void on_buttonSyncDir_clicked();
    void on_linePassword_textEdited(QString text);
    void on_lineHost_textEdited(QString text);
    void on_lineLocalDir_textEdited(QString text);
    void on_lineRemoteDir_textEdited(QString text);
    void on_lineUser_textEdited(QString text);
    void on_lineName_textEdited(QString text);
    void on_time_valueChanged(int value);
    void on_conflict_clicked();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_buttonCancel_clicked();
    void on_buttonNewAccount_clicked();

    // Owncloud related signals
    void slotToLog(QString text);
    void slotToStatus(QString text);
    void slotConflictExists(OwnCloudSync*);
    void slotConflictResolved(OwnCloudSync*);
    void slotProgressFile(qint64 value);
    void slotProgressTotal(qint64 value);
    void slotReadyToSync(OwnCloudSync*);
    void slotFinishedSync(OwnCloudSync*);
    void slotToMessage(QString caption, QString body,
    QSystemTrayIcon::MessageIcon icon);
};

#endif // SYNCWINDOW_H