
this.imagini = new Object()
var cale = $(this).text()
var w = $(this).attr("w")
var aparitie = $(this).attr("aparitie")

var imagine = document.createElement("img")
imgine.src = cale;
imagine.classList.add(aparitie);
imagini[id] = imagine

/*
getImagine(id){
	if(imagini[id].aparitie=="multipla"){
		var aux = imagini[id];
		var im_nou = document.createElement("img")
		im_nou.src = imagini[id].src
		im_nou.w = imagini[id].w
		im_nou.h = imagini[id].h
		imagini[id] = im_nou
		return aux;
	}
}
*/


/*class adversar { 
	constructor(nume, damage) {
		var putere=10;
		this.get_nota=function(){
			return putere;
		}
		this.set_putere=function(n){putere=n}
		this.nume = nume;
	}
	afis(){
		  	//
	}
}

class protagonist extends adversar {
	
	afis(){
		super.afis();
		//
	}	

}

class potiune {

}
*/