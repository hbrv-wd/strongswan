/*
 * Copyright (C) 2007 Martin Willi
 * Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#ifndef GUEST_H
#define GUEST_H

#include <library.h>
#include <utils/iterator.h>

#include "iface.h"

typedef enum guest_state_t guest_state_t;

/**
 * @brief State of a guest (started, stopped, ...)
 */
enum guest_state_t {
	/** guest kernel not running at all */
	GUEST_STOPPED,
	/** kernel started, but not yet available */
	GUEST_STARTING,
	/** guest is up and running */
	GUEST_RUNNING,
	/** guest has been paused */
	GUEST_PAUSED,
	/** guest is stopping (shutting down) */
	GUEST_STOPPING,
};

/**
 * string mappings for guest_state_t
 */
extern enum_name_t *guest_state_names;

typedef struct guest_t guest_t;

/**
 * @brief A guest is a UML instance running on the host.
 **/
struct guest_t {
	
	/**
	 * @brief Get the name of this guest.
	 *
	 * @return		name of the guest
	 */
	char* (*get_name) (guest_t *this);
	
	/**
	 * @brief Get the process ID of the guest child process.
	 *
	 * @return		name of the guest
	 */
	pid_t (*get_pid) (guest_t *this);
	/**
	 * @brief Get the state of the guest (stopped, started, etc.).
	 *
	 * @return		guests state
	 */
	guest_state_t (*get_state)(guest_t *this);	
	
	/**
	 * @brief Start the guest.
	 *
	 * @param kernel	kernel to boot for this guest
	 * @return		TRUE if guest successfully started
	 */
	bool (*start) (guest_t *this, char *kernel);
	
	/**
	 * @brief Kill the guest.
	 *
	 * @return		TRUE if guest was running and killed
	 */
	bool (*stop) (guest_t *this);
	
	/**
	 * @brief Create a new interface for that host.
	 *
	 * @param name	name of the interface in the guest
	 * @return		created interface, or NULL if failed
	 */
	iface_t* (*create_iface)(guest_t *this, char *name);
	
	/**
	 * @brief Create an iterator over all guest interfaces.
	 *
	 * @return		iterator over iface_t's
	 */
	iterator_t* (*create_iface_iterator)(guest_t *this);

	/**
	 * @brief Close and destroy a guest with all interfaces
	 */	
	void (*destroy) (guest_t *this);
};

/**
 * @brief Create a new, unstarted guest.
 *
 * @param name		name of the guest
 * @param master	read-only master filesystem for guest
 * @param mem		amount of memory to give the guest
 */
guest_t *guest_create(char *name, char *master, int mem);

#endif /* GUEST_H */

