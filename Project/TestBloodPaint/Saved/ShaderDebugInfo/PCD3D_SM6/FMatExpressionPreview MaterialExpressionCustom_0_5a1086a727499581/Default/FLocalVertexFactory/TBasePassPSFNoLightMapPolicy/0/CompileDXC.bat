@ECHO OFF
SET DXC="C:\Users\Administrator\Desktop\Unreal\UnrealEngine\Engine\Binaries\ThirdParty\ShaderConductor\Win64\dxc.exe"
IF NOT EXIST %DXC% (
	ECHO Couldn't find dxc.exe under "C:\Users\Administrator\Desktop\Unreal\UnrealEngine\Engine\Binaries\ThirdParty\ShaderConductor\Win64"
	GOTO :END
)
%DXC% -Zpr -O3 -auto-binding-space 0 -Wno-parentheses-equality -disable-lifetime-markers -T ps_6_6 -E MainPS -Fc BasePassPixelShader.d3dasm -Fo BasePassPixelShader.dxil BasePassPixelShader
:END
PAUSE
