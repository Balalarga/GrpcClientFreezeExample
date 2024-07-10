class R5GrpcExServerReactor : public grpc::ServerBidiReactor<R5GrpcExProtocol::Request, R5GrpcExProtocol::Response>
{
public:
	//- functions ---------------------------------------------------------------------------
	R5GrpcExServerReactor(
		const std::string& ServerId,
		int32 ReactorNum,
		const std::shared_ptr<class R5GrpcExServerCallbackService>& Service)
        : ServerId(ServerId)
        , ReactorNum(ReactorNum)
        , Service(Service) {
            StartRead(&Request);
            WriteNextMessage();
        }

        virtual ~R5GrpcExServerReactor() override{

        }


private:
	//- variables ---------------------------------------------------------------------------
	std::string ServerId;
	int32 ReactorNum;
	int32 MessageCounter = 0;

	R5GrpcExProtocol::Request Request;
	R5GrpcExProtocol::Response Response;

	std::shared_ptr<R5GrpcExServerCallbackService> Service;

	std::mutex FinishMutex;
	bool HasFinished = false;


	//- functions ---------------------------------------------------------------------------
	virtual void OnReadDone(bool IsOk) override{
        if (!IsOk)
        {
            FinishGracefully();
            return;
        }

        StartRead(&Request);

    }

	virtual void OnWriteDone(bool IsOk) override{
        
        if (!IsOk)
        {
            FinishGracefully();
            return;
        }

        WriteNextMessage();

    }

	virtual void OnDone() override{
        delete this;
    }
	virtual void OnCancel() override{

    }

	void WriteNextMessage()
    {
        Response.set_serverid(fmt::format("{}[{}]", ServerId, ReactorNum));
        Response.set_count(MessageCounter++);
        StartWrite(&Response);
    }

	void FinishGracefully()
    {
        std::lock_guard Lock(FinishMutex);

        if (!HasFinished)
        {
            Finish(grpc::Status::OK);
            HasFinished = true;
        }
    }

};
