package main

import (
	"fmt"
)

func In(a int, list []int) bool{
    for _, b := range list {
        if b == a {
            return true
        }
    }
    return false
}

func prenable(reines []int, ligne int) bool{
	if In(ligne, reines){
        return true
	}
	nb := len(reines)
    diagPlus := []int{}
	diagMoins := []int{}
	for i := 0; i < nb; i++ {
		diagPlus = append(diagPlus, reines[i]+i)
		diagMoins = append(diagMoins, reines[i]-i)
	}
    return In(ligne+nb, diagPlus) || In(ligne-nb, diagMoins)
}

func swaptab(a *[][]int, b *[][]int) {
    c := *a
    *a = *b
    *b = c
}

func nilTab2() [][]int{
    vide := [][]int{}
    return vide
}

func main() {
	n := 12
    sols := [][]int{}
	list := []int{}
    for k := 0; k < n; k++{
		list = append(list, k)
        sols = append(sols, list)
		list = nil
    }
	newSol := []int{}
	newSols := [][]int{}
    for c := 1; c < n; c++{
		newSols = nilTab2()
		for solution := 0; solution < len(sols); solution++ {
			for l := 0; l < n; l++{
				if !prenable(sols[solution], l){
					newSol = make([]int, c)
					copy(newSol, sols[solution])
					newSol = append(newSol, l)
					newSols = append(newSols, newSol)
				}
			}
		}
		swaptab(&sols, &newSols)
    }
	fmt.Println(len(sols)," solutions")
	fmt.Println(sols)
}