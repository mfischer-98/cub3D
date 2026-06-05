TO DO LIST

1. Replace ray marching with DDA algorithm
	- initialize struct
	- ray_line function is gonna change
	- calculate deltadist, step and side dist
	- DDA loop: compare side_x with side_y, if mapx or y == 1, hit == 1
	- calculate perpendicular distance
	- fix fish eye

2. Calculate wall height with perpendicular dist
	- make draw start e draw end, vamos desenhar as paredes por colunas

3. Floor and ceiling

4. Add all this to the render loop

5. Remove unused old functions

6. Create debug mode/tools

10. After everything, add side shading