


class R5GrpcExClientReactor : public grpc::ClientBidiReactor<R5GrpcExProtocol::Request, R5GrpcExProtocol::Response>
{
public:
	//- functions ---------------------------------------------------------------------------
	static std::weak_ptr<R5GrpcExClientReactor> Create(const std::string& ClientId,	const std::shared_ptr<grpc::Channel>& Channel){
        auto Reactor = std::make_shared<R5GrpcExClientReactor>(ClientId, Channel);
	    Reactor->Self = Reactor;

	    return Reactor;
    }

	R5GrpcExClientReactor(const std::string& ClientId, const std::shared_ptr<grpc::Channel>& Channel){
        Stub->async()->Example(&Context, this);

        StartCall();
        StartRead(&Response);
        WriteNextMessage();
    }

	virtual ~R5GrpcExClientReactor() override{
    }

	void Shutdown(){
	    Context.TryCancel();
    }

private:
	//- variables ---------------------------------------------------------------------------
	std::string ClientId;
	int32 MessageCounter = 0;

	std::weak_ptr<grpc::Channel> Channel;
	std::unique_ptr<R5GrpcExProtocol::R5GrpcExService::Stub> Stub;
	grpc::ClientContext Context;

	R5GrpcExProtocol::Request Request;
	R5GrpcExProtocol::Response Response;

	std::shared_ptr<R5GrpcExClientReactor> Self;


	//- functions ---------------------------------------------------------------------------
	virtual void OnReadDone(bool IsOk) override{
        if (IsOk)
        {
            StartRead(&Response);
        }
        else
        {
            Context.TryCancel();
        }
    }
	virtual void OnWriteDone(bool IsOk) override{
        if (IsOk)
        {
            WriteNextMessage();
        }
    }
	virtual void OnDone(const grpc::Status& Status) override{
	    Self.reset();
    }
	virtual void OnWritesDoneDone(bool IsOk) override{

    }
	virtual void OnReadInitialMetadataDone(bool IsOk) override{

    }

	void WriteNextMessage(){
        Request.set_clientid(ClientId);
        Request.set_count(MessageCounter++);

        StartWrite(&Request);
    }
};
