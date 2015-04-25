#include "string.h"
#include "ppapi/c/pp_errors.h"
#include "ppapi/c/ppp.h"
#include "ppapi/c/ppb_instance.h"
#include "ppapi/c/ppp_instance.h"
#include "ppapi/c/ppb_messaging.h"
#include "ppapi/c/ppb_var.h"
#include "ppapi/c/pp_var.h"


extern int MainNim(int argc, char** args, char** env);

static PPB_Instance* ppb_instance_interface = NULL;
static PPB_Messaging* ppb_messaging_interface = NULL;
static PPB_Var* ppb_var_interface = NULL;
static PP_Instance pp_instance = -1;

#define NIM_EXPORT
NIM_EXPORT void PostMessage(const char* message) {
	struct PP_Var message_var = ppb_var_interface->VarFromUtf8(message, strlen(message));
	ppb_messaging_interface->PostMessage(pp_instance, message_var);
	ppb_var_interface->Release(message_var);
}

static PP_Bool Instance_DidCreate(PP_Instance instance,
                                  uint32_t argc,
                                  const char* argn[],
                                  const char* argv[]) {
	if (pp_instance == -1) {
		pp_instance = instance;
		MainNim(0, NULL, NULL);
		// if (MainNim(argc, argv, argn) == 0) {
			return PP_TRUE;
		// }
	}

	return PP_FALSE;
}

static void Instance_DidDestroy(PP_Instance instance) {
	if (instance == pp_instance) {
		pp_instance = -1;
	}
}

static void Instance_DidChangeView(PP_Instance instance, PP_Resource view) {
}

static void Instance_DidChangeFocus(PP_Instance instance, PP_Bool has_focus) {
}

static PP_Bool Instance_HandleDocumentLoad(PP_Instance instance, PP_Resource url_loader) {
	return PP_TRUE;
}

PP_EXPORT const void* PPP_GetInterface(const char* interface_name) {

	if (strcmp(interface_name, PPP_INSTANCE_INTERFACE) == 0) {
		static PPP_Instance instance_interface = {
			&Instance_DidCreate,
			&Instance_DidDestroy,
			&Instance_DidChangeView,
			&Instance_DidChangeFocus,
			&Instance_HandleDocumentLoad
		};
		return &instance_interface;
	}

	return NULL;
}

PP_EXPORT int32_t PPP_InitializeModule(PP_Module a_module_id, PPB_GetInterface get_browser) {
	ppb_instance_interface = (PPB_Instance*)(get_browser(PPB_INSTANCE_INTERFACE));
	ppb_messaging_interface = (PPB_Messaging*)(get_browser(PPB_MESSAGING_INTERFACE));
	ppb_var_interface = (PPB_Var*)(get_browser(PPB_VAR_INTERFACE));
	return PP_OK;
}

PP_EXPORT void PPP_ShutdownModule() {
}
