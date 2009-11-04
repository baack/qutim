#ifndef ICONSLOADERIMPL_H
#define ICONSLOADERIMPL_H

#include "libqutim/iconloader.h"

using namespace qutim_sdk_0_3;

namespace Core
{
	class IconLoaderImpl : public IconLoader
	{
		Q_OBJECT
	public:
		IconLoaderImpl();
		virtual QIcon loadIcon(const QString &name);
		virtual QMovie *loadMovie(const QString &name);
		virtual QString iconPath(const QString &name, StdSize iconSize);
		virtual QString moviePath(const QString &name, StdSize iconSize);
	};
}

#endif // ICONSLOADERIMPL_H
