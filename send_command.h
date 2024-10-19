#ifndef SEND_COMMAND_H
#define SEND_COMMAND_H

// For user space HAL RTAPI
#ifdef RTAPI
#undef RTAPI
#endif
#ifndef ULAPI
#define ULAPI
#endif

#include <iostream>
//#include <display/variable.h>
#include <QString>

#include <emc.hh>
#include <emc_nml.hh>

#include "hal.h"
#include "rtapi.h"          /* RTAPI realtime OS API */
#include "rtapi_string.h"
#include "rtapi_errno.h"

#include "config.h"
#include "rtapi.h"          /* RTAPI realtime OS API */
#include "hal.h"            /* HAL public API decls */
#include <rtapi_mutex.h>
#include <rtapi_string.h>

#include "config.h"
#include "rtapi.h"          /* RTAPI realtime OS API */
#include "hal.h"            /* HAL public API decls */
#include "hal_priv.h"	/* private HAL decls */
#include "halcmd_commands.h"
#include <rtapi_mutex.h>
#include <rtapi_string.h>

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

static int set_common(hal_type_t type, void *d_ptr, char *value);
int set_pin_FLOAT_calc(float pinFVc, QString pinVNc);

void hal_connection(){
    //somehow we need this at the startup of lcnc, otherwise we get segmentation fault.
    int comp_id = hal_init("axis");
    hal_comp_name(comp_id);
    hal_malloc(200);
    //int sigml= hal_signal_new("xxx", HAL_FLOAT );
    hal_ready(comp_id);
}

//void hal_command_test(){
//    //to test various hal commands quite easy.
//    char value[] = "12";
//    char name[] = "halui.feed-override.counts";
//    do_setp_cmd(name,value);
//}

int do_sets_cmd(char *name, char *value) ///../linuxcnc/src/hal/utils/halcmd_commands.c
{
    int retval;
    hal_sig_t *sig;
    hal_type_t type;
    void *d_ptr;

    /*QString strOne = QString::fromLocal8Bit(name);
    char name1[strlen(strOne.toStdString().c_str()) + 0];
    char name2[strlen(strOne.toStdString().c_str()) + 0];
    char name3[strlen(strOne.toStdString().c_str()) + 0];
    qDebug() << Q_FUNC_INFO << "Received name =  " << strOne << "  ;";
    qDebug() << Q_FUNC_INFO << "Received char =  " << name << "  find by name PIN macro: " << halpr_find_pin_by_name(name) <<  "  ;";
    qDebug() << Q_FUNC_INFO << "Received char =  " << name << "  find by name PARAM macro: " << halpr_find_param_by_name(name1) <<  "  ;";*/

    //rtapi_print_msg(RTAPI_MSG_DBG, "setting signal '%s'\n", name);
    /* get mutex before accessing shared data */
    rtapi_mutex_get(&(hal_data->mutex));
    /* search signal list for name */
    sig = halpr_find_sig_by_name(name);
    if (sig == 0) {
    rtapi_mutex_give(&(hal_data->mutex));
    //qDebug() << Q_FUNC_INFO << "Param/Pin name error -- not find  ;";
    return -EINVAL;
    }
    //qDebug() << Q_FUNC_INFO << "found it - it have a writer? if it is a port we can set its buffer size ";
    if ((sig->type != HAL_PORT) && (sig->writers > 0)) {
    rtapi_mutex_give(&(hal_data->mutex));
    //qDebug() << Q_FUNC_INFO << "signal '%s' already has writer(s)";
    return -EINVAL;
    }
    //qDebug() << Q_FUNC_INFO << " no writer, so we can safely set it";
    type = sig->type;
    d_ptr = SHMPTR(sig->data_ptr);
    retval = set_common(type, d_ptr, value);
    rtapi_mutex_give(&(hal_data->mutex));
    if (retval == 0) {
    /* print success message */
   // qDebug() << Q_FUNC_INFO << "Signal '%s' set to %s\n";
    } else {
    //qDebug() << Q_FUNC_INFO << "halcmd_error  sets failed;";
    }
    return retval;
}

int do_setp_cmd(char *name, char *value)
{
    int retval;
   // hal_param_bit_new()
    hal_param_t *param;
    hal_pin_t *pin;
    hal_type_t type;
    void *d_ptr;
    QString strOne = QString::fromLocal8Bit(name);
    qDebug() << Q_FUNC_INFO << "Received SETP name =  " << strOne << "  ;";
    qDebug() << Q_FUNC_INFO << "Received char =  " << name ;

    //halcmd_info("setting parameter '%s' to '%s'\n", name, value);
    /* get mutex before accessing shared data */
    rtapi_mutex_get(&(hal_data->mutex));
    /* search param list for name */
    param = halpr_find_param_by_name(name);
    if (param == 0) {
        pin = halpr_find_pin_by_name(name);
        if(pin == 0) {
            rtapi_mutex_give(&(hal_data->mutex));
             qDebug() << Q_FUNC_INFO << "Param/Pin name error  ;";
            return -EINVAL;
        } else {
            /* found it */
            type = pin->type;
            if(pin->dir == HAL_OUT) {
                rtapi_mutex_give(&(hal_data->mutex));
                qDebug() << Q_FUNC_INFO << "pin '%s' is not writable";
                return -EINVAL;
            }
            if(pin->signal != 0) {
                rtapi_mutex_give(&(hal_data->mutex));
                qDebug() << Q_FUNC_INFO << "pin '%s' is connected to a signal";
                return -EINVAL;
            }
            // d_ptr = (void*)SHMPTR(pin->dummysig);
            d_ptr = (void*)&pin->dummysig;
        }
    } else {
        qDebug() << Q_FUNC_INFO << " found it ";
        type = param->type;
        qDebug() << Q_FUNC_INFO << " is it read only? ";
        if (param->dir == HAL_RO) {
            rtapi_mutex_give(&(hal_data->mutex));
            qDebug() << Q_FUNC_INFO << "param '%s' is not writable";
            return -EINVAL;
        }
        d_ptr = SHMPTR(param->data_ptr);
    }

    retval = set_common(type, d_ptr, value);

    rtapi_mutex_give(&(hal_data->mutex));
    if (retval == 0) {
    /* print success message */
        if(param) {
            qDebug() << Q_FUNC_INFO << "Param success!!  ;";
        } else {
            qDebug() << Q_FUNC_INFO << "Pin success!!  ;";
    }
    } else {
    qDebug() << Q_FUNC_INFO << "SETP FAILED  ;";
    }
    return retval;

}

static int set_common(hal_type_t type, void *d_ptr, char *value) {
    // This function assumes that the mutex is held
     int retval = 0;
     double fval;
     long lval;
     unsigned long ulval;
     unsigned uval;
     char *cp = value;

     switch (type) {
     case HAL_BIT:
     if ((strcmp("1", value) == 0) || (strcasecmp("TRUE", value) == 0)) {
         *(hal_bit_t *) (d_ptr) = 1;
     } else if ((strcmp("0", value) == 0)
         || (strcasecmp("FALSE", value)) == 0) {
         *(hal_bit_t *) (d_ptr) = 0;
     } else {
         //halcmd_error("value '%s' invalid for bit\n", value);
         retval = -EINVAL;
     }
     break;
     case HAL_FLOAT:
     fval = strtod ( value, &cp );
     if ((*cp != '\0') && (!isspace(*cp))) {
         /* invalid character(s) in string */
         //halcmd_error("value '%s' invalid for float\n", value);
         retval = -EINVAL;
     } else {
         *((hal_float_t *) (d_ptr)) = fval;
     }
     break;
     case HAL_S32:
     lval = strtol(value, &cp, 0);
     if ((*cp != '\0') && (!isspace(*cp))) {
         /* invalid chars in string */
         //halcmd_error("value '%s' invalid for S32\n", value);
         retval = -EINVAL;
     } else {
         *((hal_s32_t *) (d_ptr)) = lval;
     }
     break;
     case HAL_U32:
     ulval = strtoul(value, &cp, 0);
     if ((*cp != '\0') && (!isspace(*cp))) {
         /* invalid chars in string */
         //halcmd_error("value '%s' invalid for U32\n", value);
         retval = -EINVAL;
     } else {
         *((hal_u32_t *) (d_ptr)) = ulval;
     }
     break;
//     case HAL_PORT:
//         uval = strtoul(value, &cp, 0);
//         if ((*cp != '\0') && (!isspace(*cp))) {
//             //halcmd_error("value '%s' invalid for PORT\n", value);
//             retval = -EINVAL;
//         } //else {
//           //  if((*((hal_port_t*)d_ptr) != 0) && (hal_port_buffer_size(*((hal_port_t*)d_ptr)) > 0)) {
//                 //halcmd_error("port is already allocated with %u bytes.\n", hal_port_buffer_size(*((hal_port_t*)d_ptr)));
//           //      retval = -EINVAL;
//       //  } else {
//             //*((hal_port_t*) (d_ptr)) = hal_port_alloc(uval);
//       //  }
//     }
//     break;
     default:
     /* Shouldn't get here, but just in case... */
     //halcmd_error("bad type %d\n", type);
     retval = -EINVAL;
     }
     return retval;
}



void set_CL_I20_OnOff(bool pinOutValue, QString pinOutName){
    //char name[] = pinOutName.toStdString().c_str();
    //qDebug() << Q_FUNC_INFO << "func INPUT " << pinOutValue << "  &  " << pinOutName << "  ;";
    char name[strlen(pinOutName.toStdString().c_str()) + 1];  // Make sure there's enough space
    strcpy(name, pinOutName.toStdString().c_str());
    if(pinOutValue == true){ char valueOn[] = "1"; do_sets_cmd(name,valueOn);}
    else { char valueOff[] = "0"; do_sets_cmd(name,valueOff);}

}



int set_pin_FLOAT_calc(float pinFVc, QString pinVNc){

    int retval;
    hal_sig_t *sig;
    hal_type_t type;
    void *d_ptr;
    QString Htype;
   /* hal_data_u *value;
    bool *con = nullptr;
    float checkVal = 0;*/

   /* rtapi_mutex_get(&(hal_data->mutex));
    // search signal list for name
    sig = halpr_find_sig_by_name(name);
    if (sig == 0) {
    rtapi_mutex_give(&(hal_data->mutex));
    qDebug() << Q_FUNC_INFO << "Param/Pin name error -- not find  ;";
    return -EINVAL;
    }
    qDebug() << Q_FUNC_INFO << "found it - it have a writer? if it is a port we can set its buffer size ";
    if ((sig->type != HAL_PORT) && (sig->writers > 0)) {
    rtapi_mutex_give(&(hal_data->mutex));
    qDebug() << Q_FUNC_INFO << "signal '%s' already has writer(s)";
    return -EINVAL;
    }
    qDebug() << Q_FUNC_INFO << " no writer, so we can safely set it";
    type = sig->type;
    d_ptr = SHMPTR(sig->data_ptr);
    retval = set_common(type, d_ptr, value);
    rtapi_mutex_give(&(hal_data->mutex));*/

    //  ####################  qDebug() << Q_FUNC_INFO << "func INPUT FLOAT " << pinFVc << "  &  " << pinVNc << "  ;";

    char name[strlen(pinVNc.toStdString().c_str()) + 1];  // Make sure there's enough space
    strcpy(name, pinVNc.toStdString().c_str());
    rtapi_mutex_get(&(hal_data->mutex));

    sig = halpr_find_sig_by_name(name);
    type = sig->type;
    if((sig != 0) && (type == HAL_FLOAT)  && (sig->writers <= 0)){
        //rtapi_mutex_get(&(hal_data->mutex));
        d_ptr = SHMPTR(sig->data_ptr);
        *((hal_float_t *) (d_ptr)) = pinFVc;
        rtapi_mutex_give(&(hal_data->mutex));
        /*int r=hal_get_pin_value_by_name(name,&type,&value,con);
        checkVal = value->f;
        rtapi_mutex_give(&(hal_data->mutex));
        qDebug() << Q_FUNC_INFO << "sig " << name << " have these value:  " << checkVal;*/
        retval = 0;
    }
    else{
        rtapi_mutex_give(&(hal_data->mutex));
        switch (type)
                {
                case HAL_BIT:
                            Htype = "HAL_BIT";
                            break;
                case HAL_FLOAT:
                            Htype = "HAL_FLOAT";
                            break;
                case HAL_S32:
                            Htype = "HAL_S32";
                            break;
                case HAL_U32:
                            Htype = "HAL_U32";
                            break;
                default:
                            Htype = "ERROR";
                }
        qDebug() << Q_FUNC_INFO << "sig " << name << " is not writable or not exist ... type is:  " << Htype << "  and (sig>0 no good) sig->writers =   "  << sig->writers;
        retval = 100;
    }
    rtapi_mutex_give(&(hal_data->mutex));

    return retval;

}



#endif // SEND_COMMAND_H
