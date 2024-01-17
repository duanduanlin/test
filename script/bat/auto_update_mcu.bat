
set count=0
set result="method test success"

adb shell rm /oemdata/update_mcu.sh
adb push ./update_mcu.sh /oemdata/
adb shell chmod +x /oemdata/update_mcu.sh

adb push .\project_OTA.bin /oemdata/

:waitadb
echo "wait for adb connect,test count " %count%
@adb wait-for-device

:waitNormal
@timeout /nobreak /t 10
echo "wait for enter normal"
@adb pull /tmp/state_mgr_cfg.json state.json

@if not exist state.json (GOTO waitNormal)
@timeout /nobreak /t 10

:doUpdate
set /a count=count+1
adb shell ./oemdata/update_mcu.sh
@echo "update done,wait 10 sec to do next"
@timeout /nobreak /t 10
GOTO waitadb

(findstr /r %result% "output.log") && (GOTO success) || (GOTO failed)

:success
@echo "update done,wait 10 sec to do next"
@timeout /nobreak /t 10
GOTO waitadb
:failed
echo "update failed"
@pause