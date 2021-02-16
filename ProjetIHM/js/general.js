
var nom = ["Panneaux-Surprises", "Chasseur de Têtes", "Porte-à-porte", "Topi Taupe terrées", "Labyrinthe et Tuyaux"];

/* Fonction d'ajout d'un exercice dans le tableau */
function dispAddForm()
{
	document.getElementById("actionsButtons").classList.add("d-none"); // on cache les boutons

	document.getElementById("div-add").classList.remove("d-none");
}
function cancelAdd(e)
{
	e.preventDefault();
	document.getElementById("actionsButtons").classList.remove("d-none");
	document.getElementById("div-add").classList.add("d-none");

	// On nettoie le formulaire
	let datas =['ajoutNomExe', 'ajoutTypeExe', 'descrip', 'publicCible', 'dureeActiv', 'nivDifficulte', 'dateCreation', 'infoAuteur'];
	datas.forEach(function(input_id, i)
	{
		if(i != 5) // Pour garde une valeur dans le select
		{
			document.getElementById(input_id).value = "";
		}
		document.getElementById(input_id).classList.remove("is-valid");
		document.getElementById(input_id).classList.remove("is-invalid");
	})
}
function addInTab(event)
{
	event.preventDefault();
	// On récupère le(s) tbody du/des tableau(x)
	let tab = document.getElementsByTagName('tbody');

	// On récupère tous les informations du fomulaire
	let datas =['ajoutNomExe', 'ajoutTypeExe', 'descrip', 'publicCible', 'dureeActiv', 'nivDifficulte', 'dateCreation', 'infoAuteur'];
	let validForm = true;
	datas.forEach(function(input_id)
	{
		if(document.getElementById(input_id).value == "")
		{
			document.getElementById(input_id).classList.remove("is-valid");
			document.getElementById(input_id).classList.add("is-invalid");
			validForm = false;
		}
		else
		{
			document.getElementById(input_id).classList.remove("is-invalid");
			document.getElementById(input_id).classList.add("is-valid");
		}
	});

	if(validForm)
	{
		datas = datas.map(function(x, i)
		{
			if(i == 4)
			{
				let time = document.getElementById(x).value;
				time = (time == 1 ) ? time + " minute" : time + " minutes"
				return `<td>${time}</td>`;
			}
			else if (i == 6)
			{
				const d = new Date(document.getElementById(x).value);
				return `<td>${[("0"+d.getDate()).slice(-2), ("0" + (d.getMonth()+1)).slice(-2), d.getFullYear()].join('/')}</td>`
			}
			else
			{
				if(i == 0)
				{
					// On ajout dans la liste pour l'autocompletion
					nom.push(document.getElementById(x).value);
				}
				return `<td>${document.getElementById(x).value}</td>`;
			}
		});

		// Construction de la ligne du tableau
		let nbrows = tab[0].rows.length;
		let tr = `<tr><td class="d-none delbox">
	 						<div class="custom-control custom-checkbox">
							  <input type="checkbox" class="custom-control-input" id="customCheck${nbrows+1}">
							  <label class="custom-control-label" for="customCheck${nbrows+1}"></label>
							</div>	
	 					</td>`;
	 	datas.forEach(function(td)
			{
				tr += td;
			})
			tr+="</tr>";

		if(tab[0].rows.length == 0)
		{
			// On enlève le warning
			document.getElementById("msg_warning").classList.add("d-none");
			// Les boutons supprimer et modifier peuvent être actif
			document.getElementById("del-btn").removeAttribute("disabled", "");
			document.getElementById("edit-btn").removeAttribute("disabled", "")
			document.getElementById("search-ipt").removeAttribute("disabled", "");
			let tableau = document.getElementsByTagName("table");
			tableau[0].classList.remove("d-none");
			if(tableau[1] != undefined)
			{
				tableau[1].classList.remove("d-none");
			}
		}

		if(window.innerWidth < 767) // Si on est sur mobile (il y a donc 2 tbody supperposé)
		{
			tab[1].innerHTML += tr;
			tab[0].innerHTML += tr;
			tab[0].querySelector("tr:last-child td:nth-child(2)").style.display = "none";
		}
		else
		{
			tab[0].innerHTML += tr;
		}
		document.getElementById("actionsButtons").classList.remove("d-none");
		document.getElementById("div-add").classList.add("d-none");

		// Réinitialise le formulaire
		cancelAdd(event);

		// On affiche le message de succès
		document.getElementById("msg_add").classList.remove("d-none");
		setTimeout(function()
		{
			document.getElementById("msg_add").classList.add("d-none");
		}, 3000);
	}
	else
	{
		// On affiche le message d'erreur
		document.getElementById("msg_error").classList.remove("d-none");
		setTimeout(function()
		{
			document.getElementById("msg_error").classList.add("d-none");
		}, 3000);
	}
}


/* Fonction de recherche dans le tableau */
function searchInTab(event)
{
	if(event!== undefined)
	{
		event.preventDefault();
	}
	
	let table = document.getElementsByTagName('table');

	Array.from(table[0].rows).forEach(searchInRow);
	if(table[1] !== undefined)
	{
		Array.from(table[1].rows).forEach(searchInRow);
	}

	let nbrows = 0;
	Array.from(table[0].rows).forEach(function(row, i)
	{
		if(i!=0)
		{
			if(!(row.style.display == "none"))
			{
				nbrows++;
			}
		}
	})
	if(nbrows == 0)
	{
		document.getElementById("msg_noresult").classList.remove("d-none");
		table[0].classList.add("d-none");
	}
	else
	{
		document.getElementById("msg_noresult").classList.add("d-none");
		table[0].classList.remove("d-none");
	}
}

function searchInRow(row, i)
{
	let inputFilter = document.getElementById('search-ipt').value;
	if(inputFilter != '')
	{
		// On désactive les autres fonctionnalités
		document.getElementById("add-btn").setAttribute("disabled", "");
		document.getElementById("del-btn").setAttribute("disabled", "");
		document.getElementById("edit-btn").setAttribute("disabled", "");

		if(i != 0) // On ne recherche pas dans la 1ère ligne d'en-tête du tableau
		{
			// On nettoie l'ancienne recherche
			row.innerHTML = row.innerHTML.replace(/<span class="bg-primary">/g, '');
			row.innerHTML = row.innerHTML.replace(/<\/span>/g, '');

			let correspondance = false;
			Array.from(row.cells).forEach(function(td, i)
			{
				if(i != 0)
				{
					const tdContent = td.innerText;
	
					if (tdContent.toUpperCase().indexOf(inputFilter.toUpperCase()) == -1) // Il n'y a pas de correspondance 
					{
						row.style.display = "none";
					} 
					else // On a trouver une correspondance
					{
						correspondance = true;
						const regex = new RegExp(inputFilter, 'gi');
						td.innerHTML = td.innerHTML.replace(regex, `<span class="bg-primary">$&</span>`);
					}
				}
			});
			if(correspondance)
			{
				row.style.display = "";
			}
		}
	}
	else
	{
		// On active les fonctionnalités
		document.getElementById("add-btn").removeAttribute("disabled", "");
		document.getElementById("del-btn").removeAttribute("disabled", "");
		document.getElementById("edit-btn").removeAttribute("disabled", "");
		row.innerHTML = row.innerHTML.replace(/<span class="bg-primary">/g, '');
		row.innerHTML = row.innerHTML.replace(/<\/span>/g, '');
		row.style.display = "";
	}
}

function putDelClick()
{
	let table = document.getElementsByTagName('table');
	if(window.innerWidth < 767) // Si on est sur mobile (il y a donc 2 tbody supperposé)
	{
		Array.from(table[0].rows).forEach(function(row, i)
		{
			if(i!=0)
			{
				row.onclick = function()
				{
					row.cells[0].children[0].children[0].checked = !row.cells[0].children[0].children[0].checked; 
					row.classList.toggle('bg-primary');

					table[1].rows[i].classList.toggle('bg-primary');
					table[1].rows[i].cells[0].children[0].children[0].checked = !table[1].rows[i].cells[0].children[0].children[0].checked; 
				};
			}
		});
		Array.from(table[1].rows).forEach(function(row, i)
		{
			if(i!=0)
			{
				row.onclick = function()
				{
					row.cells[0].children[0].children[0].checked = !row.cells[0].children[0].children[0].checked; 
					row.classList.toggle('bg-primary');

					table[0].rows[i].classList.toggle('bg-primary');
					table[0].rows[i].cells[0].children[0].children[0].checked = !table[0].rows[i].cells[0].children[0].children[0].checked; 
				};
			}
		});
	}
	else
	{
		Array.from(table[0].rows).forEach(function(row)
		{
			row.onclick = function()
			{
				row.cells[0].children[0].children[0].checked = !row.cells[0].children[0].children[0].checked; 
			};
		});
	}
}
function removeDelClick()
{
	let table = document.getElementsByTagName('table');
	if(window.innerWidth < 767) // Si on est sur mobile (il y a donc 2 tbody supperposé)
	{
		Array.from(table[0].rows).forEach(function(row, i)
		{
			row.onclick = null;
			row.classList.remove("bg-info");
		});
		Array.from(table[1].rows).forEach(function(row, i)
		{
			row.onclick = null;
			row.classList.remove("bg-info");
		});
	}
	else
	{
		Array.from(table[0].rows).forEach(function(row)
		{
			row.onclick = null;
			row.classList.remove("bg-info");
		});
	}
}
function dispCheckBox(e)
{
	e.preventDefault();

	document.getElementById("actionsButtons").classList.add("d-none");

	// On met des onclick pour faciliter la sélection
	putDelClick();

	// On affiche le message d'indication
	document.getElementById("msg_click_del").classList.remove("d-none");

	let table = document.getElementsByTagName('table')[0];
	if(table.rows.length > 1)
	{
		Array.from(table.rows).forEach(function(tr)
		{
			tr.cells[0].classList.remove("d-none"); //display: none;
		});

		document.getElementById("actionsDel").classList.remove("d-none");
	}	
}

function hideCheckBox()
{	
	// On réinitialise les checkbox
	let table = document.getElementsByTagName('table')[0];
	Array.from(table.rows).forEach(function(tr, i)
	{
		if(i!=0)
		{
			tr.cells[0].children[0].children[0].checked = false;
		}
		tr.cells[0].classList.add("d-none");	
	});

	// On enlève le message d'indication
	document.getElementById("msg_click_del").classList.add("d-none");

	// On enlève les onclicks sur les lignes
	removeDelClick();

	document.getElementById("actionsDel").classList.add("d-none");
	document.getElementById("actionsButtons").classList.remove("d-none");
}

function deleteInTab()
{
	let table = document.getElementsByTagName('table');
	let aSupprimer = false;
	if(window.innerWidth < 767) // Si on est sur mobile (il y a donc 2 tbody supperposé)
	{
		Array.from(table[0].rows).forEach(function(tr, i)
		{
			if(i!=0)
			{
				if(tr.cells[0].children[0].children[0].checked)
				{
					tr.remove();
					nom.splice(i-1, 1);
					aSupprimer = true;
				}
			}
		});
		Array.from(table[1].rows).forEach(function(tr, i)
		{
			if(i!=0)
			{
				if(tr.cells[0].children[0].children[0].checked)
				{
					tr.remove();
					aSupprimer = true;
				}
			}
		});
	}
	else
	{
		Array.from(table[0].rows).forEach(function(tr, i)
		{
			if(i!=0)
			{
				if(tr.cells[0].children[0].children[0].checked)
				{
					tr.remove();
					nom.splice(i-1, 1);
					aSupprimer = true;
				}
			}
		});
	}
	
	if(aSupprimer)
	{
		// On affiche le message de succès
		document.getElementById("msg_del").classList.remove("d-none");
		setTimeout(function()
		{
			document.getElementById("msg_del").classList.add("d-none");
		}, 3000);
		hideCheckBox();
		let tableau = document.getElementsByTagName("table");
		if(tableau[0].rows.length == 1)
		{
			document.getElementById("del-btn").setAttribute("disabled", "");
			document.getElementById("edit-btn").setAttribute("disabled", "");
			document.getElementById("search-ipt").setAttribute("disabled", "");
			tableau[0].classList.add("d-none");
			if(tableau[1] != undefined)
			{
				tableau[1].classList.add("d-none");
			}
			// On affiche le warning
			document.getElementById("msg_warning").classList.remove("d-none");
		}
	}
	else
	{
		// On affiche le message d'erreur
		document.getElementById("msg_del_error").classList.remove("d-none");
		setTimeout(function()
		{
			document.getElementById("msg_del_error").classList.add("d-none");
		}, 3000);
	}
}
function dispModForm()
{
	document.getElementById("actionsButtons").classList.add("d-none");
	document.getElementById("div-mod").classList.remove("d-none");
}
function cancelModForm(e)
{
	e.preventDefault();
	document.getElementById("actionsButtons").classList.remove("d-none");
	document.getElementById("div-mod").classList.add("d-none");
	removeEditClick();

	const input_id = ["modifNomExe", "modifTypeExe", "moifDescrip", "moifPublicCible", "modifDureeActiv", "modifNivDifficulte", "modifDateCreation", "modifInfoAuteur"];
	// On nettoie le formulaire
	input_id.forEach(function(input_id, i)
	{
		if(i != 5) // Pour garde une valeur dans le select
		{
			document.getElementById(input_id).value = "";
		}
		document.getElementById(input_id).classList.remove("is-valid");
		document.getElementById(input_id).classList.remove("is-invalid");
	})
}

function putEditClick()
{
	let tableau = document.getElementsByTagName("tbody");
	if(window.innerWidth < 767) // Si on est sur mobile (il y a donc 2 tbody supperposé)
	{
		Array.from(tableau[0].rows).forEach(function(row, i)
		{
			row.onclick = getRowInForm(row);
			tableau[1].rows[i].onclick = getRowInForm(row);
		});
	}
	else
	{
		Array.from(tableau[0].rows).forEach(function(row)
		{
			row.onclick = getRowInForm(row);
		});
	}
}
function removeEditClick()
{
	let tableau = document.getElementsByTagName("tbody");
	if(window.innerWidth < 767) // Si on est sur mobile (il y a donc 2 tbody supperposé)
	{
		Array.from(tableau[0].rows).forEach(function(row, i)
		{
			row.onclick = null;
			tableau[1].rows[i].onclick = null;
		});
	}
	else
	{
		Array.from(tableau[0].rows).forEach(function(row)
		{
			row.onclick = null;
		});
	}
}
function getRowInForm(row)
{
	return function()
	{
		// On cache le message de sélection
		document.getElementById("selectModif").classList.add("d-none");
		document.getElementById("msg_click_edit").classList.add("d-none");

		// On enlève les onclicks sur les autres lignes
		removeEditClick();

		const input_id = ["modifNomExe", "modifTypeExe", "moifDescrip", "moifPublicCible", "modifDureeActiv", "modifNivDifficulte", "modifDateCreation", "modifInfoAuteur"];

		if(window.innerWidth < 767)
		{
			Array.from(row.cells).forEach(function(td, i)
			{
				if(i != 0) //1er td contient checkbox
				{
					if(i-1 == 4)
					{
						document.getElementById(input_id[i-1]).value = parseInt(td.innerText);
					}
					else if(i-1 == 0)
					{
						td.style.display = "";
						document.getElementById(input_id[i-1]).value = td.innerText;
						td.style.display = "none";
					}
					else if (i-1 == 6)
					{
						const date = td.innerText;
						const d = date.split("/");
						console.log([d[2],d[1],d[0]].join('-'));
						document.getElementById(input_id[i-1]).value = [d[2],d[1],d[0]].join('-');
					}
					else
					{
						document.getElementById(input_id[i-1]).value = td.innerText;
					}	
				}
			});
		}
		else
		{
			Array.from(row.cells).forEach(function(td, i)
			{
				if(i != 0) //1er td contient checkbox
				{
					if(i-1 == 4)
					{
						document.getElementById(input_id[i-1]).value = parseInt(td.innerText);
					}
					else if (i-1 == 6)
					{
						const date = td.innerText;
						const d = date.split("/");
						document.getElementById(input_id[i-1]).value = [d[2],d[1],d[0]].join('-');
					}
					else
					{
						document.getElementById(input_id[i-1]).value = td.innerText;
					}	
				}
			});
		}
		

		dispModForm(); // On affiche le formulaire remplie

		document.getElementById("form-mod").onsubmit = function(e)
		{
			e.preventDefault();

			let validForm = true;
			input_id.forEach(function(input_id)
			{
				if(document.getElementById(input_id).value == "")
				{
					document.getElementById(input_id).classList.remove("is-valid");
					document.getElementById(input_id).classList.add("is-invalid");
					validForm = false;
				}
				else
				{
					document.getElementById(input_id).classList.remove("is-invalid");
					document.getElementById(input_id).classList.add("is-valid");
				}
			});

			if(validForm)
			{
				if(window.innerWidth < 767)
				{
					Array.from(row.cells).forEach(function(td, i)
					{
						if(i != 0)
						{
							if(i-1 == 4)
							{
								const time = document.getElementById(input_id[i-1]).value;
								td.innerText = (time == 1 ) ? time + " minute" : time + " minutes"
							}
							else if (i-1 == 6)
							{
								const d = new Date(document.getElementById(input_id[i-1]).value);
								td.innerText = [("0"+d.getDate()).slice(-2), ("0" + (d.getMonth()+1)).slice(-2), d.getFullYear()].join('/');
							}
							else
							{
								if(i == 1)
								{
									nom.splice(row.rowIndex-1, 1, document.getElementById(input_id[i-1]).value);
								}
								td.innerText = document.getElementById(input_id[i-1]).value
							}
						}
					});
					let tableau = document.getElementsByTagName("tbody");
					Array.from(tableau[1].rows[row.rowIndex-1].cells).forEach(function(td, i)
					{
						if(i != 0)
						{
							if(i-1 == 4)
							{
								const time = document.getElementById(input_id[i-1]).value;
								td.innerText = (time == 1 ) ? time + " minute" : time + " minutes"
							}
							else if (i-1 == 6)
							{
								const d = new Date(document.getElementById(input_id[i-1]).value);
								td.innerText = [("0"+d.getDate()).slice(-2), ("0" + (d.getMonth()+1)).slice(-2), d.getFullYear()].join('/');
							}
							else
							{
								td.innerText = document.getElementById(input_id[i-1]).value
							}
						}
					});
				}
				else
				{
					Array.from(row.cells).forEach(function(td, i)
					{
						if(i != 0)
						{
							if(i-1 == 4)
							{
								const time = document.getElementById(input_id[i-1]).value;
								td.innerText = (time == 1 ) ? time + " minute" : time + " minutes"
							}
							else if (i-1 == 6)
							{
								const d = new Date(document.getElementById(input_id[i-1]).value);
								td.innerText = [("0"+d.getDate()).slice(-2), ("0" + (d.getMonth()+1)).slice(-2), d.getFullYear()].join('/');
							}
							else
							{
								if(i == 1)
								{
									nom.splice(row.rowIndex-1, 1, document.getElementById(input_id[i-1]).value);
								}
								td.innerText = document.getElementById(input_id[i-1]).value
							}
						}
					});
				}
				
				cancelModForm(e);
				// On affiche le message de succès
				document.getElementById("msg_edit").classList.remove("d-none");
				setTimeout(function()
				{
					document.getElementById("msg_edit").classList.add("d-none");
				}, 3000);
			}
			else
			{
				// On affiche le message d'erreur
				document.getElementById("msg_error").classList.remove("d-none");
				setTimeout(function()
				{
					document.getElementById("msg_error").classList.add("d-none");
				}, 3000);
			}
		}
	}
}

function dispModif()
{
	document.getElementById("selectModif").classList.remove("d-none");
	document.getElementById("actionsButtons").classList.add("d-none");

	// On affiche le message d'indication
	document.getElementById("msg_click_edit").classList.remove("d-none");

	putEditClick(); // Ajout des events onclick sur les lignes du tableau
}
function cancelMod(e)
{
	e.preventDefault();
	document.getElementById("selectModif").classList.add("d-none");
	document.getElementById("actionsButtons").classList.remove("d-none");
	document.getElementById("msg_click_edit").classList.add("d-none");
	removeEditClick();
}

function onDark(e)
{
	let head = document.getElementsByTagName("head")[0];
	if(e.target.checked)
	{
		let link = document.createElement('link');  
	    link.rel = 'stylesheet';  
	    link.type = 'text/css'; 
	    link.href = 'styles/bootstrapDark.css';  

    	head.appendChild(link);

    	document.getElementById("titretab").classList.remove("text-primary");
    	document.getElementById("titretab").classList.add("text-white");
	}
	else
	{
		head.removeChild(head.lastChild);

		document.getElementById("titretab").classList.add("text-primary");
    	document.getElementById("titretab").classList.remove("text-white");
	}
    
}

function hideIntro()
{
	document.getElementsByClassName("card")[0].classList.add('d-none');
}

function autocomplete(inp, arr) 
{
  /*the autocomplete function takes two arguments,
  the text field element and an array of possible autocompleted values:*/
  var currentFocus;
  /*execute a function when someone writes in the text field:*/
  inp.addEventListener("input", function(e) 
  {
      var a, b, i, val = this.value;
      /*close any already open lists of autocompleted values*/
      closeAllLists();
      if(!val) 
		{ 
			return false;
		}
      currentFocus = -1;
      /*create a DIV element that will contain the items (values):*/
      a = document.createElement("DIV");
      a.setAttribute("id", this.id + "autocomplete-list");
      a.setAttribute("class", "autocomplete-items");
      /*append the DIV element as a child of the autocomplete container:*/
      this.parentNode.appendChild(a);
      /*for each item in the array...*/
      for (i = 0; i < arr.length; i++) 
      {
        /*check if the item starts with the same letters as the text field value:*/
        if (arr[i].substr(0, val.length).toUpperCase() == val.toUpperCase()) 
        {
          /*create a DIV element for each matching element:*/
          b = document.createElement("DIV");
          /*make the matching letters bold:*/
          b.innerHTML = "<strong>" + arr[i].substr(0, val.length) + "</strong>";
          b.innerHTML += arr[i].substr(val.length);
          /*insert a input field that will hold the current array item's value:*/
          b.innerHTML += "<input type='hidden' value='" + arr[i] + "'>";
          /*execute a function when someone clicks on the item value (DIV element):*/
              b.addEventListener("click", function(e) 
              {
	              /*insert the value for the autocomplete text field:*/
	              inp.value = this.getElementsByTagName("input")[0].value;
	              /*close the list of autocompleted values,
	              (or any other open lists of autocompleted values:*/
	              searchInTab();
	              closeAllLists();
	          });
          a.appendChild(b);
        }
      }
  });
	/*execute a function presses a key on the keyboard:*/
	inp.addEventListener("keydown", function(e) 
	{
		var x = document.getElementById(this.id + "autocomplete-list");
		if (x) x = x.getElementsByTagName("div");
		if (e.keyCode == 40) 
		{
			/*If the arrow DOWN key is pressed,
			increase the currentFocus variable:*/
			currentFocus++;
			/*and and make the current item more visible:*/
			addActive(x);
		} 
		else if (e.keyCode == 38) 
		{ //up
			/*If the arrow UP key is pressed,
			decrease the currentFocus variable:*/
			currentFocus--;
			/*and and make the current item more visible:*/
			addActive(x);
		} 
		else if (e.keyCode == 13) 
		{
			/*If the ENTER key is pressed, prevent the form from being submitted,*/
			e.preventDefault();
			if (currentFocus > -1) 
			{
			  /*and simulate a click on the "active" item:*/
			  if (x) x[currentFocus].click();
			}
		}
	});
	function addActive(x) 
	{
		/*a function to classify an item as "active":*/
		if (!x) return false;
		/*start by removing the "active" class on all items:*/
		removeActive(x);
		if (currentFocus >= x.length) currentFocus = 0;
		if (currentFocus < 0) currentFocus = (x.length - 1);
		/*add class "autocomplete-active":*/
		x[currentFocus].classList.add("autocomplete-active");
	}
	function removeActive(x) 
	{
		/*a function to remove the "active" class from all autocomplete items:*/
		for (var i = 0; i < x.length; i++) 
		{
		  x[i].classList.remove("autocomplete-active");
		}
	}
	function closeAllLists(elmnt) 
	{
		/*close all autocomplete lists in the document,
		except the one passed as an argument:*/
		var x = document.getElementsByClassName("autocomplete-items");
		for (var i = 0; i < x.length; i++) 
		{
		  if (elmnt != x[i] && elmnt != inp) 
		  {
		  	x[i].parentNode.removeChild(x[i]);
		  }
		}
	}
	/*Ferme la liste lorsqu'on clique ailleurs sur la page*/
	document.addEventListener("click", function (e) 
	{
	    closeAllLists(e.target);
	});
}

// Ajout de tous les listeners 
Array.from(document.getElementsByClassName("nav-link")).forEach(link => link.addEventListener("click", menuBtnClick));

document.getElementById("del-btn").addEventListener("click", dispCheckBox);
document.getElementById("valid-delete").addEventListener("click", deleteInTab);
document.getElementById("cancel-delete").addEventListener("click", hideCheckBox);

document.getElementById("add-btn").addEventListener("click", dispAddForm);
document.getElementById("cancel-add").addEventListener("click", cancelAdd);

document.getElementById("form-add").addEventListener("submit", addInTab);

document.getElementById("search-ipt").addEventListener("input", searchInTab);
document.getElementById("search-ipt").addEventListener("focusout", searchInTab);
autocomplete(document.getElementById("search-ipt"), nom);

document.getElementById("edit-btn").addEventListener("click", dispModif);
document.getElementById("cancel-mod").addEventListener("click", cancelModForm);
document.getElementById("cancel-selectModif").addEventListener("click", cancelMod);

document.getElementById("darkSwitch").addEventListener("click", onDark);
document.getElementById("hideIntro").addEventListener("click", hideIntro);
