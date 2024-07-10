class R5GrpcExServerCallbackService
	: public R5GrpcExProtocol::R5GrpcExService::CallbackService
	, public std::enable_shared_from_this<R5GrpcExServerCallbackService>
{
public:
	//- functions ---------------------------------------------------------------------------
	R5GrpcExServerCallbackService(const std::string& ServerId)
		: ServerId(ServerId){

	}
	virtual ~R5GrpcExServerCallbackService() override{

	}

	void SetServer(const std::shared_ptr<grpc::Server>& InServer){
		Server = InServer;
	}

private:
	//- variables ---------------------------------------------------------------------------
	std::string ServerId;
	int32 ReactorCounter = 0;
	int32 ClientCounter = 0;
	int32 ClientMessageCounter = 0;
	int32 ServerMessageCounter = 0;

	std::shared_ptr<grpc::Server> Server;


	//- functions ---------------------------------------------------------------------------
	virtual grpc::ServerBidiReactor<R5GrpcExProtocol::Request, R5GrpcExProtocol::Response>* Example(
		grpc::CallbackServerContext*) override{
			return new R5GrpcExServerReactor(ServerId, ReactorCounter++, shared_from_this());
		}
};
