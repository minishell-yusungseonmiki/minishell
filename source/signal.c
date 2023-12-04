/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonmiki <seonmiki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:33:50 by seonmiki          #+#    #+#             */
/*   Updated: 2023/12/03 17:33:50 by seonmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sigint_handler(int signum)
{
	(void)signum;
	g_exit_status = 1;
    printf("\n");
    rl_on_new_line();
    // rl_replace_line("", 0);
    rl_redisplay();
}

void	sigint_heredoc(int signum)
{
	(void)signum;
	g_exit_status = -1;
	printf("\n");
	close(0);
}

void	sigint_child(int signum)
{
	(void)signum;
	g_exit_status = -130;
	printf("\n");
}

void	sigquit_child(int signum)
{
	(void)signum;
	g_exit_status = -131;
	SIG_DFL;
}

void	print_off_signal(void)
{
	struct termios	term;

	tcgetattr(1, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(1, 0, &term);
}

void	print_on_signal(void)
{
	struct termios	term; // 터미널 설정이 담겨있는 termios 구조체

	tcgetattr(1, &term); // 현재 터미널의 설정을 term에 가져옴
	term.c_lflag |= (ECHOCTL); // 시그널표식 출력이 false 라면 true로 변경
	tcsetattr(1, 0, &term);  // 변경한 term 설정을 현재 터미널에 적용
}
