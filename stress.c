//
//  stress.c
//  StressAdiumPlugin
//
//  Created by Alexey Yesipenko on 5/21/13.
//  Copyright (c) 2013 Alexey Yesipenko. All rights reserved.
//

#include <libpurple/plugin.h>
#include <libpurple/prpl.h>
#include <libpurple/debug.h>
#include <libpurple/version.h>

#define PLUGIN_ID "prpl-avy-stress"
#define PLUGIN_AUTHOR "Alexey Yesipenko <alex7y@gmail.com>"

#define CHAT_ID 3333
#define CHAT_NAME "StressChat"

static const char *
list_icon(G_GNUC_UNUSED PurpleAccount * account,
                 G_GNUC_UNUSED PurpleBuddy * buddy)
{
	return "stress";
}

static GList *
statuses(G_GNUC_UNUSED PurpleAccount * acct)
{
	GList *types = NULL;
	PurpleStatusType *status;
    
	/*Online people have a status message and also a date when it was set */
	status = purple_status_type_new_full(PURPLE_STATUS_AVAILABLE, NULL,
                                         "Online", TRUE, TRUE, FALSE);
	types = g_list_append(types, status);
    
	/*Offline people dont have messages */
	status = purple_status_type_new_full(PURPLE_STATUS_OFFLINE, NULL,
                                         "Offline", TRUE, TRUE, FALSE);
	types = g_list_append(types, status);
    
	return types;
}

static gchar *
status_text(G_GNUC_UNUSED PurpleBuddy * buddy)
{
	return NULL;
}

static void
login(PurpleAccount * account)
{
	PurpleConnection *gc = purple_account_get_connection(account);
    purple_connection_set_state(gc, PURPLE_CONNECTED);
}

static void
close(PurpleConnection * gc)
{
}

static void
set_status(G_GNUC_UNUSED PurpleAccount * acct,
                  G_GNUC_UNUSED PurpleStatus * status)
{
}

static GList *
chat_info(G_GNUC_UNUSED PurpleConnection * gc)
{
	GList *m = NULL;
	struct proto_chat_entry *pce;
    
	pce = g_new0(struct proto_chat_entry, 1);
	pce->label = "_Room:";
	pce->identifier = "room";
	pce->required = TRUE;
	m = g_list_append(m, pce);
    
	return m;
}

static char *
get_chat_name(GHashTable * data)
{
	return g_strdup(g_hash_table_lookup(data, "room"));
}

static gboolean
timer_cb(void *p)
{
    serv_got_chat_in(p, CHAT_ID, "who", 0, "message1", time(NULL));
    serv_got_chat_in(p, CHAT_ID, "who", 0, "message2", time(NULL));
    serv_got_chat_in(p, CHAT_ID, "who", 0, "message3", time(NULL));
    return TRUE;
}

static void
join_chat(PurpleConnection * gc, GHashTable * data)
{
    if (!purple_find_chat(gc, CHAT_ID)) {
        purple_debug_misc(PLUGIN_ID, "JOIN CHAT\n");
        serv_got_joined_chat(gc, CHAT_ID, CHAT_NAME);
        gc->proto_data = (void*)purple_timeout_add_seconds(1, timer_cb, gc);
    }
}

static void
chat_leave(PurpleConnection * gc, int id)
{
    purple_timeout_remove((guint)gc->proto_data);
}

int
chat_send(PurpleConnection * gc, int id, const char *message,
                 G_GNUC_UNUSED PurpleMessageFlags flags)
{
	return 0;
}

static PurplePluginProtocolInfo protocol_info = {
	/* options */
	OPT_PROTO_NO_PASSWORD, NULL,	/* user_splits */
	NULL,			/* protocol_options */
	NO_BUDDY_ICONS, list_icon,	/* list_icon */
	NULL,			/* list_emblems */
	status_text,	/* status_text */
	NULL, statuses,	/* status_types */
	NULL,			/* blist_node_menu */
	NULL,	/* chat_info */
	NULL,			/* chat_info_defaults */
	login,		/* login */
	close,		/* close */
	NULL,	/* send_im */
	NULL,			/* set_info */
	NULL,			/* send_typing */
	NULL,			/* get_info */
	set_status,	/* set_status */
	NULL,			/* set_idle */
	NULL,			/* change_passwd */
	NULL,			/* add_buddy */
	NULL,			/* add_buddies */
	NULL,			/* remove_buddy */
	NULL,			/* remove_buddies */
	NULL,			/* add_permit */
	NULL,			/* add_deny */
	NULL,			/* rem_permit */
	NULL,			/* rem_deny */
	NULL,			/* set_permit_deny */
	join_chat,	/* join_chat */
	NULL,			/* reject chat invite */
	get_chat_name,	/* get_chat_name */
	NULL,			/* chat_invite */
	chat_leave,	/* chat_leave */
	NULL,			/* chat_whisper */
	chat_send,	/* chat_send */
	NULL,			/* keepalive */
	NULL,			/* register_user */
	NULL,			/* get_cb_info */
	NULL,			/* get_cb_away */
	NULL,			/* alias_buddy */
	NULL,			/* group_buddy */
	NULL,			/* rename_group */
	NULL,			/* buddy_free */
	NULL,			/* convo_closed */
	NULL,			/* normalize */
	NULL,			/* set_buddy_icon */
	NULL,			/* remove_group */
	NULL,			/* get_cb_real_name */
	NULL,			/* set_chat_topic */
	NULL,			/* find_blist_chat */
	NULL,			/* roomlist_get_list */
	NULL,			/* roomlist_cancel */
	NULL,			/* roomlist_expand_category */
	NULL,			/* can_receive_file */
	NULL,			/* send_file */
	NULL,			/* new_xfer */
	NULL,			/* offline_message */
	NULL,			/* whiteboard_prpl_ops */
	NULL,			/* send_raw */
	NULL,			/* roomlist_room_serialize */
	NULL,			/* unregister_user */
	NULL,			/* send_attention */
	NULL,			/* attention_types */
	sizeof(PurplePluginProtocolInfo),	/* struct_size */
	NULL,			/*campfire_get_account_text_table *//* get_account_text_table */
	NULL,			/* initiate_media */
	NULL,			/* get_media_caps */
#if PURPLE_MAJOR_VERSION > 1
#if PURPLE_MINOR_VERSION > 6
	NULL,			/* get_moods */
	NULL,			/* set_public_alias */
	NULL,			/* get_public_alias */
#if PURPLE_MINOR_VERSION > 7
	NULL,			/* add_buddy_with_invite */
	NULL,			/* add_buddies_with_invite */
#endif /* PURPLE_MINOR_VERSION > 7 */
#endif /* PURPLE_MINOR_VERSION > 6 */
#endif /* PURPLE_MAJOR_VERSION > 1 */
};

static gboolean
plugin_load(G_GNUC_UNUSED PurplePlugin * plugin)
{
	return TRUE;
}

static PurplePluginInfo info = {
	PURPLE_PLUGIN_MAGIC,	/* magic number */
	PURPLE_MAJOR_VERSION,	/* purple major */
	PURPLE_MINOR_VERSION,	/* purple minor */
	PURPLE_PLUGIN_PROTOCOL,	/* plugin type */
	NULL,			/* UI requirement */
	0,			/* flags */
	NULL,			/* dependencies */
	PURPLE_PRIORITY_DEFAULT,	/* priority */
	PLUGIN_ID,		/* id */
	"Stress",		/* name */
	"1.0",			/* version */
	"Stress",		/* summary */
	"Stress",		/* description */
	PLUGIN_AUTHOR,		/* author */
	"http://pidgin.im",	/* homepage */
	plugin_load,		/* load */
	NULL,			/* unload */
	NULL,			/* destroy */
	NULL,			/* ui info */
	&protocol_info,	/* extra info */
	NULL,			/* prefs info */
	NULL,			/* actions */
	NULL,			/* reserved */
	NULL,			/* reserved */
	NULL,			/* reserved */
	NULL			/* reserved */
};

static void
init_plugin(G_GNUC_UNUSED PurplePlugin * plugin)
{
}

PURPLE_INIT_PLUGIN(stress, init_plugin, info)
