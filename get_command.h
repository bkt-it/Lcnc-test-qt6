#ifndef GET_COMMAND_H
#define GET_COMMAND_H

// For user space HAL RTAPI
#ifdef RTAPI
#undef RTAPI
#endif
#ifndef ULAPI
#define ULAPI
#endif

#include <iostream>
#include <string>
#include <vector>
#include <QString>

//#include <emc.hh>
//#include <emc_nml.hh>

#include "config.h"
//#include "task/task.hh"
//#include "task/taskclass.hh"
#include "rtapi.h"          /* RTAPI realtime OS API */
#include "hal.h"            /* HAL public API decls */
#include "hal_priv.h"	/* private HAL decls */
#include "halcmd_commands.h"
#include "halcmd.h"
#include "halcmd_completion.h"
#include <rtapi_mutex.h>
#include <rtapi_string.h>

#include <iostream>
#include <vector>
#include <QString>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <fnmatch.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <QtCore>
#include <QDebug>




float get_command(std::string name);
float get_float_pin_val(QString nV);
static char *data_value2(int type, void *valptr);
int do_gets_cmd(QString nameSig);
int do_gets_cmd1(QString nameSig);
int get_PLC_input(QString inputName);
int get_HAL_bool(QString inputBName);
int get_HMI_bool(QString inputHName);
int get_bool_command(QString nameBool);
int get_pin_command(QString namePin);



//void hal_command_test(){

//    std::string name= "ini.traj_default_velocity";
//    float result=get_command(name);
//    std::cout<<"result: "<<result<<std::endl;
//}

float get_command(std::string name){ ///../linuxcnc/src/hal/utils/halcmd_commands.c

    char text[265];
    sprintf(text,"%s",name.c_str()); //copy float value to char container

    hal_param_t *param;
    hal_pin_t *pin;
    hal_sig_t *sig = nullptr;
    hal_type_t type;
    void *d_ptr;

    //rtapi_print_msg(RTAPI_MSG_DBG, "getting parameter '%s'\n", text);
    /* get mutex before accessing shared data */
    rtapi_mutex_get(&(hal_data->mutex));
    /* search param list for name */
    param = halpr_find_param_by_name(text);
    if (param) {
        /* found it */
        type = param->type;
        d_ptr = SHMPTR(param->data_ptr);

        rtapi_mutex_give(&(hal_data->mutex));

        char *data= data_value2((int) type, d_ptr);
        std::string str(data);
        float value=std::stof(str);
        return value;
    }

    /* not found, search pin list for name */
    pin = halpr_find_pin_by_name(text);
    if(pin) {
        /* found it */
        type = pin->type;
        if (pin->signal != 0) {
            //sig = SHMPTR(sig->type);
            d_ptr = SHMPTR(sig->data_ptr);
        } else {
            sig = 0;
            d_ptr = &(pin->dummysig);
        }

        char *data= data_value2((int) type, d_ptr);
        rtapi_mutex_give(&(hal_data->mutex));

        //char *data= data_value2((int) type, d_ptr);
        /*if(strcmp(data,"TRUE")!=0){
            return 0;
        } else return 1;*/
        std::string str(data);
        float value=std::stof(str);
        return value;
    }

    rtapi_mutex_give(&(hal_data->mutex));
    //halcmd_error("pin or parameter '%s' not found\n", name);
    //return -EINVAL;
    return -1;
}


float get_float_pin_val(QString nV){
    char nHv[strlen(nV.toStdString().c_str()) + 1];  // Make sure there's enough space
    strcpy(nHv, nV.toStdString().c_str());

    //qDebug() << Q_FUNC_INFO << "converted string     " << nHv;

    hal_data_u *value;
    hal_type_t type;
    bool *con = nullptr;
    float checkVal = 0;

    //rtapi_mutex_get(&(hal_data->mutex));
    int r=hal_get_pin_value_by_name(nHv,&type,&value,con);
    //rtapi_mutex_give(&(hal_data->mutex));
        if(r!=0){
            //std::cout<<"error from /libhal/hal_interface function"<<std::endl;
            checkVal = -1;
        }
        else {
            checkVal = value->f;
            //rtapi_mutex_give(&(hal_data->mutex));
        }
        //rtapi_mutex_get(&(hal_data->mutex));

        // std::cout << "matrix.time function result:"<<ok<< std::endl;
         //std::cout << "matrix.time function result:"<<value->f<< std::endl;

         //qDebug() << Q_FUNC_INFO << "converted string     " << nHv << "   Value:   " << value->f;

        return checkVal;
}





/*int get_common(hal_type_t type, void *d_ptr, QString& value)
{

int retval = 0;
int bitval = 0;
double fval = 0;
long lval = 0;
unsigned long ulval = 0;
QString str;

rtapi_mutex_get(&(hal_data->mutex));

    switch (type)
        {
        case HAL_BIT:
                    bitval = *(hal_bit_t *) (d_ptr);
                    rtapi_mutex_give(&(hal_data->mutex));
                    str.asprintf("%d", bitval);
                    break;
        case HAL_FLOAT:
                    fval = *((hal_float_t *) (d_ptr));
                    rtapi_mutex_give(&(hal_data->mutex));
                    qDebug() << Q_FUNC_INFO <<  "value HAL_FLOAT = " << fval;
                    str.asprintf("%f", fval);
                    break;
        case HAL_S32:
                    lval =  *((hal_s32_t *) (d_ptr));
                    rtapi_mutex_give(&(hal_data->mutex));
                    str.asprintf("%ld", lval);
                    break;
        case HAL_U32:
                    ulval = *((hal_u32_t *) (d_ptr));
                    rtapi_mutex_give(&(hal_data->mutex));
                    str.asprintf("%lu", ulval);
                    break;
        default:

                    retval = -EINVAL;
        }

        //qDebug() << Q_FUNC_INFO <<  "str string = " << str;
    value = str;
        qDebug() << Q_FUNC_INFO <<  "value string = " << value;
    return 0;
}*/



int do_gets_cmd(QString nameSig)
{
    hal_sig_t *sig = nullptr;
    hal_type_t type;
    void *d_ptr;
    char *value_str = {};
    static char buf[18];
    std::string str_false = "FALSE";
    std::string str_true = "TRUE";
    std::string str_unknow = "unknown_type";
    int valBIT  = 10;
    char name[strlen(nameSig.toStdString().c_str()) + 1];  // Make sure there's enough space
    strcpy(name, nameSig.toStdString().c_str());

   // qDebug() << Q_FUNC_INFO << "get signal receive ...." << name;
    /* get mutex before accessing shared data */
    rtapi_mutex_get(&(hal_data->mutex));
    /* search signal list for name */
    sig = halpr_find_sig_by_name(name);
    if (sig == 0) {
        rtapi_mutex_give(&(hal_data->mutex));
       // qDebug() << Q_FUNC_INFO << "get signal not find ...." << name;
        valBIT = 10;
    }
    else{
        //rtapi_mutex_get(&(hal_data->mutex));
        ////qDebug() << Q_FUNC_INFO << "get signal FIND ...." << name;
        type = sig->type;
        //qDebug() << Q_FUNC_INFO << "get signal FIND .... VALID HAL_TYPE for sig  :" << name << " ,   value....:" << type;
        if(sig->writers > 0){

           //qDebug() << Q_FUNC_INFO << "get bool receive .... case HAS WRITER" ;
            d_ptr = SHMPTR(sig->data_ptr);
            if(type == HAL_BIT){
                if (*((hal_bit_t *) d_ptr) == 0){
                   // strcpy(value_str, str_false.c_str());
                    rtapi_mutex_give(&(hal_data->mutex));
                    valBIT = 0;
                    //value_str = "FALSE";
                   // qDebug() << Q_FUNC_INFO << "get bool receive .... case HAL_BIT:   " << valBIT  << "value from sig->name ...." << name;
                }
                else{
                   // strcpy(value_str, str_true.c_str());
                    rtapi_mutex_give(&(hal_data->mutex));
                    valBIT = 1;
                    //value_str = "TRUE";
                   // qDebug() << Q_FUNC_INFO << "get bool receive .... case HAL_BIT:   " << valBIT  << "value from sig->name ...." << name;
                    }
            }
            else if(type == HAL_FLOAT){
            snprintf(buf, 16, "%.7g", (double)*((hal_float_t *) d_ptr));
            rtapi_mutex_give(&(hal_data->mutex));
            value_str = buf;
           // qDebug() << Q_FUNC_INFO << "get bool receive .... case HAL_FLOAT"  << "value from sig->name ...." << name;
            }
            else if(type == HAL_S32){
            snprintf(buf, 16, "%ld", (long)*((hal_s32_t *) d_ptr));
            rtapi_mutex_give(&(hal_data->mutex));
            value_str = buf;
          //  qDebug() << Q_FUNC_INFO << "get bool receive .... case HAL_S32"   << "value from sig->name ...." << name;
            }
            else if(type == HAL_U32){
            snprintf(buf, 16, "%ld", (unsigned long)*((hal_u32_t *) d_ptr));
            rtapi_mutex_give(&(hal_data->mutex));
            value_str = buf;
          //  qDebug() << Q_FUNC_INFO << "get bool receive .... case HAL_U32"  << "value from sig->name ...." << name;
            }
            else if(type == HAL_PORT){
            //snprintf(buf, 16, "%ld", (unsigned long)*((hal_u32_t *) d_ptr));
            rtapi_mutex_give(&(hal_data->mutex));
           // value_str = buf;
           // qDebug() << Q_FUNC_INFO << "get bool receive .... case HAL_PORT"  << "value from sig->name ...." << name;
            }
            else if(type == HAL_TYPE_UNINITIALIZED){
            //snprintf(buf, 16, "%ld", (unsigned long)*((hal_u32_t *) d_ptr));
            rtapi_mutex_give(&(hal_data->mutex));
           // value_str = buf;
           // qDebug() << Q_FUNC_INFO << "get bool receive .... HAL_TYPE_UNINITIALIZED"  << "value from sig->name ...." << name;
            }
            else if(type == HAL_TYPE_UNSPECIFIED){
            //snprintf(buf, 16, "%ld", (unsigned long)*((hal_u32_t *) d_ptr));
            rtapi_mutex_give(&(hal_data->mutex));
           // value_str = buf;
           // qDebug() << Q_FUNC_INFO << "get bool receive .... case HAL_TYPE_UNSPECIFIED"  << "value from sig->name ...." << name;
            }
        //    case HAL_PORT:
        //    //snprintf(buf, 14, "%u", hal_port_buffer_size(*((hal_port_t*) valptr)));
        //    value_str = buf;
        //    break;

            else{
            /* Shouldn't get here, but just in case... */
           // qDebug() << Q_FUNC_INFO << "get signal FIND ....NO VALID HAL_TYPE for sig  :" << name << " ,  type....:" << type;
            strcpy(value_str, str_unknow.c_str());
            valBIT = 10;
            //value_str = "unknown_type";
           // //qDebug() << Q_FUNC_INFO << "get bool receive .... case DEFAULT break" ;

            }
            //d_ptr = SHMOFF(sig->data_ptr);

            rtapi_mutex_give(&(hal_data->mutex));

        }
        else{
            rtapi_mutex_give(&(hal_data->mutex));
            valBIT = 10;
            ////qDebug() << Q_FUNC_INFO << "get bool receive .... case HAS NOT  WRITER" ;
        }
       // qDebug() << Q_FUNC_INFO << "get signal SET TO ... but not return:  " << name << " ,  type....:" << type;
        //return valBIT;


       // if(valBIT !=0){ return 0; //qDebug() << Q_FUNC_INFO << "get signal FIND ....SET TO 1  " << name;}
       // else if(valBIT==0) {return 1; //qDebug() << Q_FUNC_INFO << "get signal FIND ....SET TO 0  " << name;}
       // else {return 10; //qDebug() << Q_FUNC_INFO << "get signal FIND ....SET TO 10  NOT HAL BIT" << name;}
       // if(strcmp(data,"TRUE")!=0){ return 0; //qDebug() << Q_FUNC_INFO << "get signal FIND ....SET TO 1  " << name;}
        //else if(strcmp(data,"TRUE")==0) {return 1; //qDebug() << Q_FUNC_INFO << "get signal FIND ....SET TO 0  " << name;}
      //  else {return 10; //qDebug() << Q_FUNC_INFO << "get signal FIND ....SET TO 10  " << name;}

    }

   /* if(valBIT !=0){ return 0; //qDebug() << Q_FUNC_INFO << "get signal FIND ....SET TO 1  " << name;}
    else if(valBIT==0) {return 1; //qDebug() << Q_FUNC_INFO << "get signal FIND ....SET TO 0  " << name;}
    else {return 10; //qDebug() << Q_FUNC_INFO << "get signal FIND ....SET TO 10  NOT HAL BIT" << name;}*/
    //qDebug() << Q_FUNC_INFO << "get signal SET TO ...:  " << valBIT;
    return valBIT;

  // qDebug() << Q_FUNC_INFO << "get signal SET TO ...:  " << valBIT << "get signal SET TO ...:  " << name << " ,  type....:" << type;


}



int do_gets_cmd1(QString nameSig) {
    hal_sig_t *sig = nullptr;
    void *data_ptr;
    int result = -1; // Default error value if signal not found or uninitialized type
    //char name[strlen(nameSig.toStdString().c_str()) + 1];  // Make sure there's enough space
   // strcpy(name, nameSig.toStdString().c_str());

    // Lock the mutex before accessing the shared data
    rtapi_mutex_get(&(hal_data->mutex));

    // Scan all signals
    for (sig = (hal_sig_t *)SHMPTR(hal_data->sig_list_ptr); sig; sig = (hal_sig_t *)SHMPTR(sig->next_ptr)) {
        // Compare current signal name with the desired one using QString
        if (nameSig == QString::fromUtf8(sig->name)) {
            // Found the signal with the desired name
            data_ptr = SHMPTR(sig->data_ptr); // Get the data pointer of the signal

            // Process signal based on its type
            switch (sig->type) {
                case HAL_FLOAT: {
                    double value = *(hal_float_t *)data_ptr;
                    // Use the value as needed
                    //qDebug() << "HAL_FLOAT value: " << value;
                    result = 0; // Assuming 0 indicates success
                    break;
                }
                case HAL_BIT: {
                    bool value = *(hal_bit_t *)data_ptr;
                    // Use the value as needed
                    //qDebug() << "HAL_BIT value: " << value;
                    result = 0; // Assuming 0 indicates success
                    break;
                }
                case HAL_U32: {
                    unsigned int value = *(hal_u32_t *)data_ptr;
                    // Use the value as needed
                   // qDebug() << "HAL_U32 value: " << value;
                    result = 0; // Assuming 0 indicates success
                    break;
                }
                case HAL_S32: {
                    int value = *(hal_s32_t *)data_ptr;
                    // Use the value as needed
                    //qDebug() << "HAL_S32 value: " << value;
                    result = 0; // Assuming 0 indicates success
                    break;
                }
                // Add other cases for different HAL types as needed
                default:
                    //qDebug() << Q_FUNC_INFO << "Unknown or uninitialized HAL type for signal:" << nameSig;
                    result = -1; // Signal type is unknown or uninitialized
                    break;
            }
            break; // Break the loop since we found the signal
        }
    }

    // Release the mutex
    rtapi_mutex_give(&(hal_data->mutex));

    return result; // Return the result, which is 0 on success or -1 on failure
}




static char *data_value2(int type, void *valptr)
{
    char *value_str;
    static char buf[18];
    std::string str_false = "FALSE";
    std::string str_true = "TRUE";
    std::string str_unknow = "unknown_type";


    switch (type) {
    case HAL_BIT:
    if (*((char *) valptr) == 0){
        //strcpy(value_str, str_false.c_str());
        value_str = "FALSE";
        ////qDebug() << Q_FUNC_INFO << "get bool receive .... case HAL_BIT:  FALSE" ;
    }
    else{
        strcpy(value_str, str_true.c_str());
        value_str = "TRUE";
        ////qDebug() << Q_FUNC_INFO << "get bool receive .... case HAL_BIT:  TRUE" ;
        }
    break;
    case HAL_FLOAT:
    snprintf(buf, 16, "%.7g", (double)*((hal_float_t *) valptr));
    value_str = buf;
    ////qDebug() << Q_FUNC_INFO << "get bool receive .... case HAL_FLOAT" ;
    break;
    case HAL_S32:
    snprintf(buf, 16, "%ld", (long)*((hal_s32_t *) valptr));
    value_str = buf;
    ////qDebug() << Q_FUNC_INFO << "get bool receive .... case HAL_S32" ;
    break;
    case HAL_U32:
    snprintf(buf, 16, "%ld", (unsigned long)*((hal_u32_t *) valptr));
    value_str = buf;
   // //qDebug() << Q_FUNC_INFO << "get bool receive .... case HAL_U32" ;
    break;
//    case HAL_PORT:
//    //snprintf(buf, 14, "%u", hal_port_buffer_size(*((hal_port_t*) valptr)));
//    value_str = buf;//qDebug() << Q_FUNC_INFO << "get signal SET TO ...:  " << valBIT;
//    break;

    default:
    /* Shouldn't get here, but just in case... */
    strcpy(value_str, str_unknow.c_str());
    //value_str = "unknown_type";
   // //qDebug() << Q_FUNC_INFO << "get bool receive .... case DEFAULT break" ;
    break;
    }
    return value_str;
}







int get_bool_command(QString nameBool){ ///../linuxcnc/src/hal/utils/halcmd_commands.c


    //qDebug() << Q_FUNC_INFO << "get bool receive ...." << text;

    //char text[1];
    //sprintf(text,"%s",name.c_str()); //copy float value to char container
    hal_data_u *value;
    bool *con = nullptr;
    hal_param_t *param;
    hal_pin_t *pin;
    hal_sig_t *sig = nullptr;
    hal_type_t type;
    void *d_ptr;
    char *value_str = {};
    static char buf[18];
    std::string str_false = "FALSE";
    std::string str_true = "TRUE";
    std::string str_unknow = "unknown_type";
    char text[strlen(nameBool.toStdString().c_str()) + 1];  // Make sure there's enough space
    strcpy(text, nameBool.toStdString().c_str());

    //rtapi_print_msg(RTAPI_MSG_DBG, "getting parameter '%s'\n", text);
    /* get mutex before accessing shared data */
    rtapi_mutex_get(&(hal_data->mutex));
    /* search param list for name */
    param = halpr_find_param_by_name(text);
    if (param) {
        //qDebug() << Q_FUNC_INFO << "get bool receive ....found PARAM" ;
        type = param->type;
        d_ptr = SHMPTR(param->data_ptr);

        rtapi_mutex_give(&(hal_data->mutex));

        char *data= data_value2((int) type, d_ptr);

        if(strcmp(data,"TRUE")!=0){
            return 0;
        } else return 1;
    }
    rtapi_mutex_give(&(hal_data->mutex));

    rtapi_mutex_get(&(hal_data->mutex));

    /* not found, search pin list for name */
    pin = halpr_find_pin_by_name(text);


   /* int r=hal_get_pin_value_by_name(text,&type,&value,con);
    if(r!=0){
        std::cout<<"error from /libhal/hal_interface function"<<std::endl;
    }
    return value->s;*/


    if(pin != 0) {
        //qDebug() << Q_FUNC_INFO << "get bool receive ....found PIN" << text;
        type = pin->type;
        if (pin->signal != 0) {
            //sig = SHMPTR(pin->signal);
            d_ptr = SHMPTR(sig->data_ptr);
             //qDebug() << Q_FUNC_INFO << "pin->signal != 0" ;
        } else {
            sig = 0;
            d_ptr = &(pin->dummysig);
             //qDebug() << Q_FUNC_INFO << "pin->signal == 0" ;
        }

        //char *data= data_value2((int) type, d_ptr);

        rtapi_mutex_give(&(hal_data->mutex));

        char *data= data_value2((int) type, d_ptr);

        if(strcmp(data,"TRUE")!=0){
            //qDebug() << Q_FUNC_INFO << "get bool receive .... (strcmp(data,'TRUE')!=0)" ;
            return 0;
        } else return 1;
    }

    rtapi_mutex_give(&(hal_data->mutex));
    //qDebug() << Q_FUNC_INFO << "get bool receive ....found NOTHING WITH NAME" << text;
    //return -EINVAL;
    return -1;
}


int get_pin_command(QString namePin){ ///../linuxcnc/src/hal/utils/halcmd_commands.c


   // qDebug() << Q_FUNC_INFO << "get bool receive ...." << namePin;

    //char text[1];
    //sprintf(text,"%s",name.c_str()); //copy float value to char container
    hal_data_u *value;
    bool *con = nullptr;
    //hal_param_t *param;
    hal_pin_t *pin;
    //hal_sig_t *sig = nullptr;
    hal_type_t type;
    //void *d_ptr;
    //char *value_str = {};
    //static char buf[18];
    std::string str_false = "FALSE";
    std::string str_true = "TRUE";
    std::string str_unknow = "unknown_type";
    int desired = 0;
    char text[strlen(namePin.toStdString().c_str()) + 1];  // Make sure there's enough space
    strcpy(text, namePin.toStdString().c_str());


    rtapi_mutex_get(&(hal_data->mutex));

    /* not found, search pin list for name */
    pin = halpr_find_pin_by_name(text);

    if(pin != 0) {
        type = pin->type;
    }

    rtapi_mutex_give(&(hal_data->mutex));

    if(pin != 0) {
        int r=hal_get_pin_value_by_name(text,&type,&value,con);
        if(r!=0){
            //std::cout<<"error from /libhal/hal_interface function"<<std::endl;
        }
        desired = value->s;
    }

    if((desired>0) && (pin != 0)){
       // qDebug() << Q_FUNC_INFO << "get bool receive .... (strcmp(data,'TRUE')!=0)" ;
        return 1;
    }
    else if (pin == 0) return -1;
    else return 0;

    //qDebug() << Q_FUNC_INFO << "get pin receive " << text << "ret val ..." << desired ;

}








int get_PLC_input(QString inputName)
{
    //qDebug() << Q_FUNC_INFO << "get pin receive inside system " ;
    char namePi[strlen(inputName.toStdString().c_str()) + 1];  // Make sure there's enough space
    strcpy(namePi, inputName.toStdString().c_str());
    //std::string namePi = inputName.toStdString();
    //qDebug() << Q_FUNC_INFO << "get pin receive inside system ALL OK" ;
    if (do_gets_cmd(inputName) == 1) return 1;
    else if (do_gets_cmd(inputName) == 10) {
        //qDebug() << Q_FUNC_INFO << "value of signal or signal is not find or not inizialized" ;
        return 0;}
    else return 0;

}

int get_HAL_bool(QString inputBName)
{
    char nameBPi[strlen(inputBName.toStdString().c_str()) + 1];  // Make sure there's enough space
    strcpy(nameBPi, inputBName.toStdString().c_str());
    //std::string namePi = inputName.toStdString();
    if (get_bool_command(inputBName) == 1) return 1;
    //if (1 == 1) return 1;
    else return 0;

}

int get_HMI_bool(QString inputHName)
{
    char nameHPi[strlen(inputHName.toStdString().c_str()) + 1];  // Make sure there's enough space
    strcpy(nameHPi, inputHName.toStdString().c_str());
    //std::string namePi = inputName.toStdString();
    if (get_pin_command(inputHName) == 1) return 1;
    //if (1 == 1) return 1;
    else return 0;

}



#endif // GET_COMMAND_H










