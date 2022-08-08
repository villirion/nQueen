package main

import (
	"fmt"
)

func permutations(arr []int)[][]int{
    var helper func([]int, int)
    res := [][]int{}
    helper = func(arr []int, n int){
        if n == 1{
            tmp := make([]int, len(arr))
            copy(tmp, arr)
            res = append(res, tmp)
        } else {
            for i := 0; i < n; i++{
                helper(arr, n - 1)
                if n % 2 == 1{
                    tmp := arr[i]
                    arr[i] = arr[n - 1]
                    arr[n - 1] = tmp
                } else {
                    tmp := arr[0]
                    arr[0] = arr[n - 1]
                    arr[n - 1] = tmp
                }
            }
        }
    }
    helper(arr, len(arr))
    return res
}

func contains(s []int, e int) bool {
    for _, a := range s {
        if a == e {
            return true
        }
    }
    return false
}

func set(strList []int) []int {
    list := []int{}
    for _, item := range strList {
        if contains(list, item) == false {
            list = append(list, item)
        }
    }
    return list
}

func diag(reines []int)bool{
		nb := len(reines)
		diagPlus := []int{}
		for i := 0; i < nb; i++ {
			diagPlus = append(diagPlus, reines[i]+i)
		}
		diagMoins := []int{}
		for i := 0; i < nb; i++ {
			diagMoins = append(diagMoins, reines[i]-i)
		}
		if len(set(diagPlus)) == nb && len(set(diagMoins)) == nb{
			return true
		}
	return false
}

func main() {
	n := 10
	sol := [][]int{}
	l := []int{}
	for i := 0; i < n; i++ {
		l = append(l, i)
	}
	perm := [][]int{}
	perm = permutations(l)
	for _, posR := range perm{
		if diag(posR){
			sol = append(sol, posR)
		}
	}
	fmt.Println(len(sol)," solutions")
	fmt.Println(sol)
}
