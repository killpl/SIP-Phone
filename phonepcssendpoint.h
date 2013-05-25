#ifndef PHONEPCSSENDPOINT_H
#define PHONEPCSSENDPOINT_H

#include <ep/pcss.h>

class phonePCSSEndpoint : public OpalPCSSEndPoint
{
public:
    phonePCSSEndpoint(OpalManager& manager);

    PBoolean OnShowIncoming(const OpalPCSSConnection & connection);
    PBoolean OnShowOutgoing(const OpalPCSSConnection & connection);
};

#endif // PHONEPCSSENDPOINT_H
