/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 17:12:42 by graja             #+#    #+#             */
/*   Updated: 2022/12/04 15:58:22 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "RBtree.hpp"
#include <vector>

int	main(int argc,char **argv)
{
	long			n;
	long			nbr;
	int			max;
	int			i;
	char			*chk;
	int			flag;
	std::vector<long>	delme;
	ft::RBtree<long, int>	test;
	ft::RBtree<long, int>::valPtr	dataptr;

	i = 0;
	srandom(time(NULL));
	if (argc < 3)
	{
		printf("\nUSE: rnd <n element> <max value> <-1|0|1>\n\n");
		return (0);
	}
	n = atoi(argv[1]);
	max = atoi(argv[2]);
	if (n > max)
	{
		printf("\nERROR: n is larger than max possible value\n\n");
		return (0);
	}
	if (argv[3])
		flag = atoi(argv[3]);
	else
		flag = 0;
	chk = (char *)calloc(max * 2 + 1, sizeof(char));
	if (!chk)
		return (0);
	while (n > 0 && i < n)
	{
		nbr = random() % max;
		if (flag == -1)
			nbr += 1;
		if (((random() % 2) && !flag) || (flag == -1))
			nbr *= -1;
		if ((nbr < 0 && !chk[nbr * -1]) || (nbr >= 0 && !chk[max + nbr]))
		{
			//printf("%ld ", nbr);
			test.insert(nbr, random()%100);
			delme.push_back(nbr);
			i++;
			if (nbr < 0)
				chk[nbr * -1] = 1;
			else
				chk[max + nbr] = 1;
		}
	}
	dataptr = test.getValue(delme[(n / 2)]);
	if (dataptr)
		std::cout << ">>> FOUND: " << dataptr->second << " value of key_nr: " << 
			dataptr->first << std::endl;
	test.setValue(delme[(n / 2)], 666);
	dataptr = test.getValue(delme[(n / 2)]);
	if (dataptr)
		std::cout << ">>> FOUND: " << dataptr->second << " value of key_nr: " << 
			dataptr->first << std::endl;
	test.erase(dataptr);
	i = 0;
	while (i < n)
	{
		nbr = random() % delme.size();
		std::cout << i << ") Delete nbr " << nbr << " with key value of " << delme[nbr] << 
			std::endl;
		test.erase(delme[nbr]);
		delme.erase(delme.begin() + nbr);
		i++; 
		std::cout << std::endl;
	}
	free(chk);
	std::cout << test.size() << std::endl;
	return (0);
}
