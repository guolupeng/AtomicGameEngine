//
// Copyright (c) 2014-2016 THUNDERBEAST GAMES LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include <Atomic/Engine/Application.h>

namespace Atomic
{

    class JSVM;

    class AppBase : public Application
    {
        ATOMIC_OBJECT(AppBase, Application)

    public:
        /// Construct.
        AppBase(Context* context);
        virtual ~AppBase();

        /// 引擎初始化前的设置. 
        virtual void Setup();
        /// 引擎初始化后的设置.
        virtual void Start();
        /// 主循环后的清理. 
        virtual void Stop();

        /// 运行一个帧，如果引擎退出，返回true
        bool RunFrame();

        virtual void Shutdown() { Stop(); }

        /// 在初始化应用程序以插入参数之前调用Called before initializing application for inserting arguments
        static void AddArgument(const String& argument);

        /// Returns the number of arguments specified on the commandline and added with AddArgument
        static unsigned GetNumArguments();

        /// Returns an argument from the list of arguments specified on the commandline or added with AddArgument
        static String GetArgument(unsigned index);

        virtual void ProcessArguments();

        static void AddEngineConfigSearchPath(const String& path) { engineConfigSearchPaths_.Push(path); }

        /// Returns whether a debugger is attached to the process (currently Windows only)
        static bool GetDebuggerAttached();

    protected:
		//读取引擎配置
        void ReadEngineConfig();

        static Vector<String> arguments_;
        static Vector<String> engineConfigSearchPaths_;

        SharedPtr<JSVM> vm_;

    private:

        void HandleLogMessage(StringHash eventType, VariantMap& eventData);
        void HandleJSError(StringHash eventType, VariantMap& eventData);

    };

}
