classdef px4HostTarget_TCPIP_Write < matlab.System
    % px4HostTarget_TCPIP_Write sends data over a TCP/IP connection.

    % Copyright 2020-2025 The MathWorks, Inc.

    % Pre-computed constants
    properties(Access = private)
        %tcpip object
        t
    end

    methods

        % Constructor
        function obj = px4HostTarget_TCPIP_Write(varargin)
            coder.allowpcode('plain');
            % Support name-value pair arguments
            setProperties(obj,nargin,varargin{:});
        end

    end

    methods(Access = private)
        function cleanUp(obj)
            % Clear the persistent TCP object in case of communication
            % error
            obj.t = [];
            px4HostTarget_tcpsingleton.getInstance('flush');
        end
    end

    methods(Access = protected)
        function setupImpl(obj)
            % Get the persistence instance of TCP object
            obj.t = px4HostTarget_tcpsingleton.getInstance();
        end

        function stepImpl(obj,input)
            % Send sensor data
            try
                obj.t.send(input);
            catch ME
                obj.cleanUp();
                rethrow(ME);
            end
        end

        function resetImpl(~)
            % Initialize / reset discrete-state properties
        end

        function releaseImpl(obj)
            obj.cleanUp();
        end
    end

    methods(Access=protected)
        function num = getNumInputsImpl(~)
            % Define total number of inputs for system with optional inputs
            num = 1;
        end

        function validateInputsImpl(~,in)
            if ~isa(in,'uint8')
                error('Input data to TCP Write to PX4 Host Target block must be uint8.');
            end
        end

        function maskDisplayCmds = getMaskDisplayImpl(~)
            LocalIPPort = ['sprintf(''Port: %d'',' num2str(uint32(4560)) ')'];

            maskDisplayCmds = [ ...
                ['color(''white'');',newline]...
                ['plot([100,100,100,100]*1,[100,100,100,100]*1);',newline]...
                ['plot([100,100,100,100]*0,[100,100,100,100]*0);',newline]...
                ['color(''black'');',newline]...
                ['sppkgroot = strrep(codertarget.pixhawk.internal.getSpPkgRootDir(),''\'',''/'');',newline]...
                ['image(fullfile(sppkgroot,''resources'',''TCP.jpg''),''center'')',newline]...
                ['color(''black'');', newline] ...
                ['text(50,12,' LocalIPPort ' ,''horizontalAlignment'', ''center'');', newline], ...
                ];

        end

    end

    methods(Static, Access=protected)
        function header = getHeaderImpl()
            header = matlab.system.display.Header(mfilename('class'),...
                'ShowSourceLink', false, ...
                'Title','TCP Write to PX4 Host Target', ...
                'Text', ['This TCP connection is in Server mode with Port 4560. The PX4 Host Target will connect to this Port.' newline newline ...
                'The block accepts a 1-D array of type uint8.']);
        end
    end

    methods (Static, Access=protected)
        function simMode = getSimulateUsingImpl(~)
            simMode = 'Interpreted execution';
        end

        function isVisible = showSimulateUsingImpl
            isVisible = false;
        end
    end

end
