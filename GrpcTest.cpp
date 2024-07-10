
void TestBody(){
    using namespace std::chrono_literals;

	// create server
	R5GrpcExServer Server;

	// create clients
	for (int32 Count = 0; Count < 10; ++Count)
	{
		auto Thread = std::thread(
			[Count]()
			{
				for (int32 Index = 0; Index < 100; ++Index)
				{
					R5GrpcExClient Client;
					std::this_thread::sleep_for(20ms);
				}
			});
		Thread.detach();
	}

	// wait and die
	std::this_thread::sleep_for(1s);
}

int main(){
    // Works ok
    TestBody();
    // Deadlock
    TestBody();
}