


class R5GrpcExServer
{
public:
	//- functions ---------------------------------------------------------------------------
	R5GrpcExServer() : ServerId(fmt::format("Sv_{}", Guid().ToString()))
    {
        auto Address = fmt::format("0.0.0.0:{}", R5GrpcEx::ServerPort);

        Service = std::make_shared<R5GrpcExServerCallbackService>(ServerId);

        grpc::ServerBuilder Builder;
        Builder.AddListeningPort(Address, grpc::InsecureServerCredentials());
        Builder.RegisterService(Service.get());
        Server = Builder.BuildAndStart();

        Service->SetServer(Server);
    }

	~R5GrpcExServer(){
        if (Server)
            Server->Shutdown();
    }

	void Shutdown(){
        if (Server)
            Server->Shutdown();
    }


private:
	//- variables ---------------------------------------------------------------------------
	std::string ServerId;
	std::shared_ptr<R5GrpcExServerCallbackService> Service;
	std::shared_ptr<grpc::Server> Server;
};
