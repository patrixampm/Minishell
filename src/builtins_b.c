/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:06:33 by aehrl             #+#    #+#             */
/*   Updated: 2025/04/02 17:01:16 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// step 1 figure out a alphabetized copy algorythm for the export
//  --> For this it might be usefull to use the lists
// --> when initializing the list add declare -x (honestly could just add this to a print function)
// step 2 when I add to the export without a value it just adds to the export (without =) (in alphabetical order)
// step 3 when I add a value to a name it adds it to the env (last item) and either updates or adds to the export


//figure out a way to set USER and then set 
/* ft_builtin_export(t_proc *p, char **env, char **exp)
{
	//if arg count == 1 then just print export 
	//if arg count > 1 then do either add to env && exp or just to exp
	// 
	if ()
} */


void	ft_add_env_front(t_env **lst, t_env *new)
{
	t_env	*aux;

	aux = new;
	if (!new || !lst)
		return ;
	aux->next = *lst;
	*lst = aux;
}


void	ft_add_node_env_back(t_env **lst, t_env *new)
{
	t_env	*aux;
	t_env	*last_node;
	
	aux = new;
	if (!new || !lst)
		return ;
	aux->next = NULL;
	last_node = ft_last_env(*lst);
	last_node->next = aux;
}

void	ft_slipin_node_env(t_env *lst, t_env *new)
{
	new->next = lst->next;
	lst->next = &new;
}

t_env *ft_initiate_export(char **env)
{
	t_env *
	t_env	*export;
	t_env	*node;
	t_env	*aux;
	int		check;

	aux = ft_create_env_lst(env);
	export = ft_new_env(aux->name, aux->content);
	aux = aux->next;
	while (aux->next != NULL)
	{
		check = ft_strncmp(export->name, new->name)
		if (check < 0)
		{
			node = ft_new_env(aux->name, aux->content);
			ft_add_env_back(&export, node);
		}
		else if (check >= 0)
		{
			node = ft_new_env(aux->name, aux->content);
			ft_slipin_node_env(&export, node);
		}
	}

}

// create a a switch function
// if we find that a list entry should come before fire function exp_switch_node(t_env *node1, t_env *node2, int pos);
// store next pointer node 1
// store next pointer node 2.
// change node1->next unless it = node 2 then change node1->next to node2->next
// change node2->next to point to node 1;
// go through the list with i (to get the position of what should point to previous node2->next)
//	make node[i]->next == original node2->next






/* WITHOUT ENV (env -i) 
declare -x OLDPWD
declare -x PWD="/home/aehrl"
declare -x SHLVL="1"


*/
/*
STANDARD WITH ENV
SYSTEMD_EXEC_PID=3349794
FT_HOOK_NAME=login-user
SESSION_MANAGER=local/c3r5s1.42malaga.com:@/tmp/.ICE-unix/3346381,unix/c3r5s1.42malaga.com:/tmp/.ICE-unix/3346381
OPAMROOT=/home/aehrl/.opam
GNOME_TERMINAL_SCREEN=/org/gnome/Terminal/screen/715433e1_bf85_4ed4_bf3b_75f34b675c2a
LANGUAGE=en
LANG=en_US.UTF-8
SSH_AUTH_SOCK=/run/user/104852/keyring/ssh
XDG_CURRENT_DESKTOP=ubuntu:GNOME
XDG_SESSION_CLASS=user
FT_HOOK_PATHNAME=login-user.d
XDG_GREETER_DATA_DIR=/var/lib/lightdm-data/aehrl
LIBVIRT_DEFAULT_URI=qemu:///system
GPG_AGENT_INFO=/run/user/104852/gnupg/S.gpg-agent:0:1
DESKTOP_SESSION=ubuntu
QT_IM_MODULE=ibus
XDG_MENU_PREFIX=gnome-
XDG_SESSION_PATH=/org/freedesktop/DisplayManager/Session15
PWD=/home/aehrl
USER=aehrl
DOTNET_BUNDLE_EXTRACT_BASE_DIR=/home/aehrl/.cache/dotnet_bundle_extract
VTE_VERSION=6800
DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/104852/bus
RUSTUP_HOME=/usr/local/rustup
DOCKER_HOST=unix:///run/user/104852/docker.sock
SSH_AGENT_LAUNCHER=gnome-keyring
GTK_MODULES=gail:atk-bridge
XDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/etc/xdg
GTK_IM_MODULE=ibus
XDG_SESSION_DESKTOP=ubuntu
KRB5CCNAME=FILE:/tmp/krb5cc_104852_fLaKUy
HOME=/home/aehrl
GNOME_DESKTOP_SESSION_ID=this-is-deprecated
QT_ACCESSIBILITY=1
XDG_DATA_DIRS=/usr/share/ubuntu:/usr/share/gnome:/home/aehrl/.local/share/flatpak/exports/share:/var/lib/flatpak/exports/share:/usr/local/share:/usr/share:/var/lib/snapd/desktop
LOGNAME=aehrl
GNOME_TERMINAL_SERVICE=:1.112
XDG_SEAT_PATH=/org/freedesktop/DisplayManager/Seat0
PATH=/home/aehrl/bin:/home/aehrl/.cargo/bin:/usr/local/cargo/bin:/home/aehrl/.opam/default/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/aehrl/.dotnet/tools:/usr/local/go/bin
XDG_RUNTIME_DIR=/run/user/104852
XMODIFIERS=@im=ibus
SHELL=/bin/zsh
XDG_SESSION_TYPE=x11
_=/usr/bin/env
OPAMSWITCH=default
MACADDRESS=3c:7d:0a:1c:24:55
GDM_LANG=en
XAUTHORITY=/home/aehrl/.Xauthority
COLORTERM=truecolor
IM_CONFIG_PHASE=1
TERM=xterm-256color
GDMSESSION=ubuntu
DISPLAY=:0
CARGO_HOME=/home/aehrl/.cargo
SHLVL=1
OLDPWD=/home/aehrl
ZSH=/home/aehrl/.oh-my-zsh
PAGER=less
LESS=-R
LSCOLORS=Gxfxcxdxbxegedabagacad
LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.webp=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:
MAIL=aehrl@student.42malaga.com
 */