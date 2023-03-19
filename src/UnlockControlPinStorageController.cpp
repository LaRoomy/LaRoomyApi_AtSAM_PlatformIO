#include "UnlockControlPinStorageController.h"

FlashStorage(unlock_control_storage_data, UNLOCKCONTROL_STORAGE_DATA);

bool UnlockControlPinStorageController::unlockControlPinStorageControllerInstanceCreated = false;
UnlockControlPinStorageController* UnlockControlPinStorageController::ucpInstance = nullptr;

UnlockControlPinStorageController::UnlockControlPinStorageController()
{}

UnlockControlPinStorageController::~UnlockControlPinStorageController()
{
    unlockControlPinStorageControllerInstanceCreated = false;
}

UnlockControlPinStorageController* UnlockControlPinStorageController::GetInstance()
{
    if(unlockControlPinStorageControllerInstanceCreated)
    {
        return ucpInstance;
    }
    else
    {
        ucpInstance = new UnlockControlPinStorageController();
        if(ucpInstance != nullptr)
        {
            unlockControlPinStorageControllerInstanceCreated = true;
        }
        return ucpInstance;
    }
}

String UnlockControlPinStorageController::loadPin(){
    // default value
    String pin("12345");

    // load data
    UNLOCKCONTROL_STORAGE_DATA ucData;
    unlock_control_storage_data.read(&ucData);

    // validate data
    if(ucData.isValid == 1){
        ucData.ucPin[10] = '\0';
        pin = ucData.ucPin;
    }

    return pin;
}

bool UnlockControlPinStorageController::savePin(const String& pin){

    // validate pin length
    if(pin.length() > 0 && pin.length() < 11){
        
        // set data to save
        UNLOCKCONTROL_STORAGE_DATA ucData;
        ucData.isValid = 1;
        strcpy(ucData.ucPin, pin.c_str());

        // save
        unlock_control_storage_data.write(ucData);
        return true;
    }
    return false;
}