#pragma once

template<>
class SvnCommand<LockRequest>
{
public:
	bool Run(SvnTask& task, LockRequest& req, LockResponse& resp)
	{
		std::string cmd = "lock ";
		cmd += Join(Paths(req.assets), " ", "\"");
		APOpen cppipe = task.RunCommand(cmd);

		std::string line;
		while (cppipe->ReadLine(line))
		{
			req.conn.Log() << line << "\n";
		}

		const bool recursive = false;
		task.GetStatus(req.assets, resp.assets, recursive);
			
		resp.Write();
		return true;
	}
};
