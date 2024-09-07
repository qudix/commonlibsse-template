SKSEPluginLoad(const SKSE::LoadInterface* a_skse)
{
	SKSE::Init(a_skse, true);

	logs::info("Hello World!");

	return true;
}
