-- object is a table
player = {
	Role = "Ardilla",
	Name = "Pilla",
	Ability = "trolldom",
	Level = 80
}

players = {}
player[0] = player
player[1]= {
	Role = "Ardilla",
	Name = "Pilla",
	Ability = "trolldom",
	Level = 80}

function addSomething( a, b )
	print("LUA called with "..a.." , "..b.." final \n")
	return a+b
end

function getPlayer(index)
	return players[index]
end

