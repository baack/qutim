/****************************************************************************
**
** qutIM - instant messenger
**
** Copyright © 2011 Ruslan Nigmatullin <euroelessar@yandex.ru>
**
*****************************************************************************
**
** $QUTIM_BEGIN_LICENSE$
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see http://www.gnu.org/licenses/.
** $QUTIM_END_LICENSE$
**
****************************************************************************/
#ifndef CHATVIEWFACTORY_H
#define CHATVIEWFACTORY_H

#include <QWidget>
#include "chatlayer_global.h"
#include <qutim/message.h>
#include <QDebug>

namespace qutim_sdk_0_3
{
class ChatSession;
class ChatUnit;
class Message;
}

namespace Core
{
namespace AdiumChat
{

class ChatSessionImpl;
class ChatViewWidget;
class ChatViewController;

class ChatViewFactory
{
public:
	virtual ~ChatViewFactory() {}
	virtual QWidget *createViewWidget() = 0;
	virtual QObject *createViewController() = 0;
};

class ChatViewWidget
{
public:
	virtual ~ChatViewWidget() {}
	virtual void setViewController(QObject *controller) = 0;
};

class ChatViewController
{
public:
	virtual ~ChatViewController() {}
	virtual void setChatSession(qutim_sdk_0_3::ChatSession *session) = 0;
	virtual qutim_sdk_0_3::ChatSession *getSession() const = 0;
	virtual void appendMessage(const qutim_sdk_0_3::Message &msg) = 0;
	virtual void clearChat() {}
	virtual QString quote() { return QString(); }
protected:
	enum FetchingStatus {
		Fetching,
		Appending,
		Done
	};

	FetchingStatus m_fetchingHistory = Fetching;
	QList<qutim_sdk_0_3::Message> m_awaitingMessages;

	void appendAwaitingMessages() {
		using qutim_sdk_0_3::Message;

		std::stable_sort(m_awaitingMessages.begin(), m_awaitingMessages.end(), [](const Message &left, const Message &right) {
			return left.time() < right.time();
		});

		for(auto m = m_awaitingMessages.begin(); m != m_awaitingMessages.end(); m++) {
			appendMessage(*m);
		}

		m_awaitingMessages.clear();
	}
};

}
}

Q_DECLARE_INTERFACE(Core::AdiumChat::ChatViewFactory, "org.qutim.core.ChatViewFactory")
Q_DECLARE_INTERFACE(Core::AdiumChat::ChatViewWidget, "org.qutim.core.ChatViewWidget")
Q_DECLARE_INTERFACE(Core::AdiumChat::ChatViewController, "org.qutim.core.ChatViewController")

#endif // CHATVIEWFACTORY_H

