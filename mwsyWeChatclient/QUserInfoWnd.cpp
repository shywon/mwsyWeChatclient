#include "QUserInfoWnd.h"
#include "QSimpleSplit.h"
#include <QApplication>
#include <QPixmap>
#include "QDataManager.h"
#include "QMainWnd.h"

QUserInfoWnd::QUserInfoWnd(QWidget* p /*= nullptr*/) : QWidget(p)
{
	setAttribute(Qt::WA_StyledBackground);
	setWindowFlags(Qt::FramelessWindowHint);
	setFixedSize(300, 240);
	setStyleSheet("background:white");

	m_vLayout = new QVBoxLayout();
	setLayout(m_vLayout);

	m_vLayout->addSpacing(25);

	//
	m_hLayout1 = new QHBoxLayout();
	m_vLayout1 = new QVBoxLayout();
	m_vLayout2 = new QVBoxLayout();

	QFont ft;
	ft.setPointSize(15);

	m_usernameLabel = new QLabel();
	m_userIdLabel = new QLabel();

	m_usernameLabel->setFont(ft);
	ft.setPointSize(12);
	m_userIdLabel->setFont(ft);

	m_usernameLabel->setText("xxxxxx");
	m_userIdLabel->setText("΢�ź�:xxxxxx");

	m_vLayout1->addWidget(m_usernameLabel);
	m_vLayout1->addWidget(m_userIdLabel);

	//
	m_hLayout1->addLayout(m_vLayout1);

	m_headLabel = new QLabel(this);
	m_headLabel->setFixedSize(40, 40);

	m_headLabel->setPixmap(QPixmap("./img/head2.png"));
	//int64_t userid = QMainWnd::getSinletonInstance()->m_userid;
	//QPixmap pixmap = QDataManager::getInstance()->m_UserId2HeadImgMap[userid];
	//m_headLabel->setPixmap(pixmap);

	m_changeHeadImgBtn = new QPushButton();
	m_changeHeadImgBtn->setText("�޸�ͷ��");
	m_changeHeadImgBtn->setFixedWidth(50);
	m_changeHeadImgBtn->setStyleSheet("background-color:#1aad19;");


	m_vLayout2->addWidget(m_headLabel);
	m_vLayout2->addWidget(m_changeHeadImgBtn);

	m_hLayout1->addLayout(m_vLayout2);
	m_vLayout->addLayout(m_hLayout1);

	{
		QSimpleSplit* sp = new QSimpleSplit();
		m_vLayout->addWidget(sp);
	}

	m_vLayout->addStretch();
}

bool QUserInfoWnd::event(QEvent* event) {
	if (event->type() == QEvent::ActivationChange)
	{
		if (QApplication::activeWindow() != this)
		{
			this->hide();
		}
	}

	return QWidget::event(event);
}
