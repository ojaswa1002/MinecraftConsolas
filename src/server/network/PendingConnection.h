#pragma once

#include <memory>

#include "network/packet/DisconnectPacket.h"
#include "network/packet/PacketListener.h"

class Connection;
class LoginPacket;
class MinecraftServer;
class Packet;
class Random;
class Socket;

class PendingConnection : public PacketListener {
private:
    static const int FAKE_LAG               = 0;
    static const int MAX_TICKS_BEFORE_LOGIN = 20 * 30;

    //    public static Logger logger = Logger.getLogger("Minecraft");
    static Random* random;

public:
    Connection* connection;

public:
    bool done;

private:
    MinecraftServer*             server;
    int                          _tick;
    std::wstring                 name;
    std::shared_ptr<LoginPacket> acceptedLogin;
    std::wstring                 loginKey;

public:
    PendingConnection(
        MinecraftServer*    server,
        Socket*             socket,
        const std::wstring& id
    );
    ~PendingConnection();
    void         tick();
    void         disconnect(DisconnectPacket::eDisconnectReason reason);
    virtual void handlePreLogin(std::shared_ptr<PreLoginPacket> packet);
    virtual void handleLogin(std::shared_ptr<LoginPacket> packet);
    virtual void handleAcceptedLogin(std::shared_ptr<LoginPacket> packet);
    virtual void onDisconnect(
        DisconnectPacket::eDisconnectReason reason,
        void*                               reasonObjects
    );
    virtual void handleGetInfo(std::shared_ptr<GetInfoPacket> packet);
    virtual void handleKeepAlive(std::shared_ptr<KeepAlivePacket> packet);
    virtual void onUnhandledPacket(std::shared_ptr<Packet> packet);
    void         send(std::shared_ptr<Packet> packet);
    std::wstring getName();
    virtual bool isServerPacketListener();

private:
    void sendPreLoginResponse();
};
