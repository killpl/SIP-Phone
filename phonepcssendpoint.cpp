#include "phonepcssendpoint.h"

phonePCSSEndpoint::phonePCSSEndpoint(OpalManager& manager):OpalPCSSEndPoint(manager)
{
}

PBoolean phonePCSSEndpoint::OnShowIncoming(const OpalPCSSConnection & /*connection*/) { return PTrue; }
PBoolean phonePCSSEndpoint::OnShowOutgoing(const OpalPCSSConnection & /*connection*/) { return PTrue; }
