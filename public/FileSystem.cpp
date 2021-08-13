/*
*
*    This program is free software; you can redistribute it and/or modify it
*    under the terms of the GNU General Public License as published by the
*    Free Software Foundation; either version 2 of the License, or (at
*    your option) any later version.
*
*    This program is distributed in the hope that it will be useful, but
*    WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*    General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software Foundation,
*    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*    In addition, as a special exception, the author gives permission to
*    link the code of this program with the Half-Life Game Engine ("HL
*    Engine") and Modified Game Libraries ("MODs") developed by Valve,
*    L.L.C ("Valve").  You must obey the GNU General Public License in all
*    respects for all of the code used other than the HL Engine and MODs
*    from Valve.  If you modify this file, you may extend this exception
*    to your version of the file, but you are not obligated to do so.  If
*    you do not wish to do so, delete this exception statement from your
*    version.
*
*/

#include	"extdll.h"
#include    "FileSystem.h"

#include <cassert>

IFileSystem *g_pFileSystem = nullptr;
CSysModule *g_pFileSystemModule = nullptr;

bool LoadFileSystem()
{
	// Determine which filesystem to use.
#if defined ( _WIN32 )
	char* szFsModule = "filesystem_stdio.dll";
#elif defined(OSX)
	char* szFsModule = "filesystem_stdio.dylib";
#elif defined(LINUX)
	char* szFsModule = "filesystem_stdio.so";
#else
#error
#endif


	char szFSDir[MAX_PATH];
	szFSDir[0] = 0;
#ifdef CLIENT_DLL
	if (gEngfuncs.COM_ExpandFilename(szFsModule, szFSDir, sizeof(szFSDir)) == FALSE)
	{
		return false;
	}
#else
	//Just use the filename for the server. No COM_ExpandFilename here.
	strcpy(szFSDir, szFsModule);
#endif

	// Get filesystem interface.
	g_pFileSystemModule = Sys_LoadModule(szFSDir);
	assert(g_pFileSystemModule);
	if (!g_pFileSystemModule)
	{
		return false;
	}

	CreateInterfaceFn fileSystemFactory = Sys_GetFactory(g_pFileSystemModule);
	if (!fileSystemFactory)
	{
		return false;
	}

	g_pFileSystem = (IFileSystem*)fileSystemFactory(FILESYSTEM_INTERFACE_VERSION, nullptr);
	assert(g_pFileSystem);
	if (!g_pFileSystem)
	{
		return false;
	}

	return true;
}

void ShutdownFileSystem()
{
	if (g_pFileSystemModule)
	{
		Sys_UnloadModule(g_pFileSystemModule);
		g_pFileSystemModule = nullptr;
	}
}
