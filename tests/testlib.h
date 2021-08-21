/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testlib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 16:14:46 by smun              #+#    #+#             */
/*   Updated: 2021/08/21 20:27:39 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTLIB_H
# define TESTLIB_H

# define do_test_stdout(testfunc, compare_str) \
	__do_test_stdout_real(testfunc, __FILE__, __LINE__, compare_str)
# define do_test_newline(testfunc, max_newlines) \
	__do_test_count_newline_real(testfunc, __FILE__, __LINE__, max_newlines)
# define do_test(testfunc) \
	__do_test(testfunc, __func__, __FILE__, __LINE__)

void		print_test_result(int argc, const char *module_name);
int			__do_test(void(*testfunc)(), const char *func, const char *file, int line);
int			__do_test_stdout_real(void(*testfunc)(), const char *file, int line, const char *compare);
int			__do_test_count_newline_real(void(*testfunc)(), const char *file, int line, int max_newline_count);
int			assert_leaks(void);

#endif
