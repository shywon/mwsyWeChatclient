#include "QCommContactItemWnd.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "QDataManager.h"

QCommContactItemWnd::QCommContactItemWnd(QWidget* p)
	: QWidget(p)
{
	
}

QCommContactItemWnd::QCommContactItemWnd(QWidget* p, const char* headUrl, const char* name, bool bNewFriend/* = false*/, int friendid/* = -1*/)
	:QWidget(p),m_bNewFriend(bNewFriend),m_friendId(friendid) 
{
	m_hLayout = new QHBoxLayout(this);
	m_hLayout->setSpacing(0);
	setLayout(m_hLayout);
	m_headUrl = new QLabel();

	m_headUrl->setPixmap(QPixmap(headUrl));
	m_headUrl->setFixedSize(40, 40);
	m_name = new QLabel();

	m_name->setText(name);
	m_hLayout->addWidget(m_headUrl);
	m_hLayout->addSpacing(15);
	m_hLayout->addWidget(m_name);

	//
	QString imgurl = QString("http://49.232.169.205:8080/UploadDemo/img/%1.png").arg(friendid);
	m_networkMgr = new QNetworkAccessManager();
	connect(m_networkMgr, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(slot_replyFinished(QNetworkReply*)));
	m_networkMgr->get(QNetworkRequest(QUrl(imgurl)));

	setFixedHeight(65);
	setObjectName("QCommContactItemWnd");
	setStyleSheet("#QCommContactItemWnd{border-bottom:1px solid red;}");
}

void QCommContactItemWnd::slot_replyFinished(QNetworkReply* reply)
{
	if (reply->error() == QNetworkReply::NoError)
	{
		QPixmap pixmap;
		pixmap.loadFromData(reply->readAll());
		pixmap = pixmap.scaled(40,40);
		m_headUrl->setPixmap(pixmap);
		QDataManager::getInstance()->m_UserId2HeadImgMap[m_friendId] = pixmap;
	}
}

