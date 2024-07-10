


class R5GrpcExClient
{
public:
	//- functions ---------------------------------------------------------------------------
	R5GrpcExClient() : ClientId(fmt::format("Cl_{}", Guid().ToString())
    {
        auto Address = fmt::format("127.0.0.1:{}", R5GrpcEx::ServerPort);

        Channel = CreateChannel(Address, grpc::InsecureChannelCredentials());
        Reactor = R5GrpcExClientReactor::Create(ClientId, Channel);
    }
	~R5GrpcExClient(){

    }

private:
	//- variables ---------------------------------------------------------------------------
	std::string ClientId;
	std::shared_ptr<grpc::Channel> Channel;

	std::weak_ptr<R5GrpcExClientReactor> Reactor;
};
