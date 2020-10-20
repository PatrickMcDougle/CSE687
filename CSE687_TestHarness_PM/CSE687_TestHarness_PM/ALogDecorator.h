#pragma once

#ifndef __A_LOG_DECORATOR_H__
#define __A_LOG_DECORATOR_H__

#include "ILogComponent.h"


namespace logger {

	class ALogDecorator : public ILogComponent
	{
	private:
		ILogComponent* log_component_;

	public:
		ALogDecorator(ILogComponent* component);

		string logInfo(data::ILogData& logData) const override;
	};
}

#endif // !__A_LOG_DECORATOR_H__