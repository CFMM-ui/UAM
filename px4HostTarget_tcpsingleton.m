classdef px4HostTarget_tcpsingleton < handle
    % px4HostTarget_tcpsingleton creates a unique instance of a TCP object,
    % which is used for reading from and writing to TCP blocks.


    % Copyright 2020-2026 The MathWorks, Inc.

    properties(Constant)
        % Library name for TCP infrastruture in rtiostream
        rtioStreamLib = 'libmwrtiostreamtcpip';
        % Set server port to 4560 as PX4 client communicates through this port.
        serverPort = 4560;
    end

    methods(Static)
        function tcpobj = getInstance(varargin)
            % Create a persistent instance of TCP object since this is used
            % both in TCP Read and Write blocks
            persistent uniqueTcpObj;

            if(nargin==0)
                if isempty(uniqueTcpObj)
                    if ispc
                        tcpipLib = [px4HostTarget_tcpsingleton.rtioStreamLib '.dll'];
                    else
                        tcpipLib = [px4HostTarget_tcpsingleton.rtioStreamLib '.so'];
                    end
                    rtiotcpip = rtw.connectivity.RtIOStreamWrapper(tcpipLib);
                    % Set the arguments to create a TCP server using rtiostream infra
                    args = {'-port', num2str(px4HostTarget_tcpsingleton.serverPort), '-protocol','TCP','-client', '0', '-blocking', '0', '-verbose', '0'};
                    rtiotcpip.setOpenRtIOStreamArgList(args);
                    rtiotcpip.open('uint8');
                    uniqueTcpObj = rtiotcpip;
                    tcpobj = uniqueTcpObj;
                else
                    tcpobj = uniqueTcpObj;
                end
            elseif(strcmp(varargin{1},'flush'))
                if ~isempty(uniqueTcpObj)
                    px4HostTarget_tcpsingleton.killPx4SimulatorProcesses();
                    % Close the server
                    retVal = rtiostream_wrapper(uniqueTcpObj.getRtIOStreamLib,...
                        'close', uniqueTcpObj.getStreamID);
                    vars = whos;
                    vars = vars([vars.persistent]);
                    varName = {vars.name};
                    clear(varName{:});
                    if (retVal ~= 0)
                        error(message('Connectivity:target:ErrorClosingChannel'));
                    end
                end
            end
        end
        function killPx4SimulatorProcesses()
            % This is required to kill the persistent variable tcp obj,
            % otherwise this port will be blocked
            % This is called from releaseImpl of tcpipread/tcpipwrite

            if ispc
                px4Exe = '/bin/px4$';
                px4Simulator = 'px4-simulator_mavlink';
                px4ExePIDs = px4.internal.wsl.WSLUtil.findPIDSWSL('Pattern',px4Exe,'Flag','-f');
                px4SimulatorPIDs = px4.internal.wsl.WSLUtil.findPIDSWSL('Pattern',px4Simulator,'Flag','-f');
                sitlPIDs = [px4ExePIDs;px4SimulatorPIDs];
                for i=numel(sitlPIDs):-1:1
                    if isempty(regexp(sitlPIDs{i}, '[a-z]', 'once'))
                        exePID = strip(sitlPIDs{i});
                        if ~isempty(exePID)
                            px4.internal.wsl.WSLUtil.executeCommandInWSL(['kill ' exePID], false);
                            pause(0.3);
                        end
                    end
                end
            else
                sitlPIDs = 'pgrep -f ''/bin/px4$'' ; pgrep -f ''px4-simulator_mavlink''';
                [~,exePIDList] = system(sitlPIDs);
                exePIDList = regexp(exePIDList, '\d+', 'match');
                if ~isempty(exePIDList)
                    for i=numel(exePIDList):-1:1
                        simPID = strip(exePIDList{i});
                        if ~isempty(simPID)
                            [~, ~] = system(['kill ' simPID]);
                            pause(0.3);
                        end
                    end
                end
            end
        end
    end
end
