#pragma once
#include <QObject>
#include <QUrl>
#include "libGitWrap/Repository.hpp"

#include "models/commithistorymodel.h"

#include <QFutureWatcher>

class BranchesManager;

class StatusMessage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(StatusCode code MEMBER code CONSTANT FINAL)
    Q_PROPERTY(QString message MEMBER message CONSTANT FINAL)
public:
    explicit StatusMessage(QObject *parent = nullptr);

    enum StatusCode
    {
        Loading,
        Ready,
        Error
    };  Q_ENUM(StatusCode)

    StatusCode code = StatusCode::Ready;
    QString message;
};


class Project : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Project)

    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)

    Q_PROPERTY(StatusMessage* status READ status NOTIFY statusChanged FINAL)

    Q_PROPERTY(QString title READ getTitle NOTIFY titleChanged)
    Q_PROPERTY(QUrl logo READ getLogo NOTIFY logoChanged)
    Q_PROPERTY(QString currentBranch READ currentBranch WRITE setCurrentBranch NOTIFY currentBranchChanged)
    Q_PROPERTY(QVariantMap currentBranchRemote READ currentBranchRemote NOTIFY currentBranchRemoteChanged)
    Q_PROPERTY(QVariantMap headBranch READ getHeadBranch NOTIFY headBranchChanged)

    Q_PROPERTY(CommitHistoryModel *commitsModel READ getCommitsModel CONSTANT FINAL)
    Q_PROPERTY(BranchesManager* branches READ getBranches CONSTANT FINAL)
    Q_PROPERTY(QStringList repoStatus READ repoStatus NOTIFY repoStatusChanged)
    Q_PROPERTY(QUrl readmeFile READ readmeFile NOTIFY readmeFileChanged CONSTANT)
    Q_PROPERTY(QVariantList remotesModel READ getRemotesModel NOTIFY remotesModelChanged)

public:    

    explicit Project(QObject *parent = nullptr);
    ~Project();

    QString url() const;

    /**
     * @brief setUrl
     * @param url
     */
    void setUrl(const QString &url);

    [[nodiscard]] QString getTitle() const;

    QUrl getLogo() const;

    QString currentBranch() const;
    void setCurrentBranch(const QString &currentBranch);

    CommitHistoryModel * getCommitsModel();

    BranchesManager* getBranches();

    QStringList repoStatus() const;
    QUrl readmeFile() const;

    QVariantList getRemotesModel() const;

    QVariantMap currentBranchRemote() const;

    QVariantMap getHeadBranch() const;

    StatusMessage* status() const;

public Q_SLOTS:
    QString fileStatusIcon(const QString &file);

    QVariantMap commitAuthor(const QString &id);
    QVariantMap remoteInfo(const QString &remoteName);

    void pull();
    void clone(const QString &url);

private:
    QFutureWatcher<void> *m_cloneWatcher;

    QString m_url;
    QString m_remoteUrl;

    Git::Repository m_repo;

    QString m_title;

    QUrl m_logo;

    QString m_currentBranch;

    CommitHistoryModel *m_commitsModel;
    BranchesManager *m_branchesManager;

    QStringList m_repoStatus;

    QUrl m_readmeFile;

    QVariantList m_remotesModel;

    QVariantMap m_currentBranchRemote;
    QVariantMap m_headBranch;
    StatusMessage *m_status;

    void setData(const QString &url);

    void setCurrentBranchRemote(const QString &currentBranch);
    void setHeadBranch();

    void setStatus(StatusMessage::StatusCode code, const QString &message);

Q_SIGNALS:
    void titleChanged(QString title);
    void logoChanged(QUrl logo);
    void urlChanged(QString url);
    void error(QString message);
    void currentBranchChanged(QString currentBranch);
    void repoStatusChanged(QStringList status);
    void readmeFileChanged(QUrl readmeFile);
    void remotesModelChanged(QVariantList remotesModel);
    void currentBranchRemoteChanged(QVariantMap currentBranchRemote);
    void headBranchChanged(QVariantMap headBranch);
    void remoteUrlChanged(QString remoteUrl);
    void statusChanged();
};



