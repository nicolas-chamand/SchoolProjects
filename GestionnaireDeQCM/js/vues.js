/* global state getQuizzes */

// //////////////////////////////////////////////////////////////////////////////
// HTML : fonctions génération de HTML à partir des données passées en paramètre
// //////////////////////////////////////////////////////////////////////////////

// génération d'une liste de quizzes avec deux boutons en bas
const htmlQuizzesList = (quizzes, curr, total) => 
{
	console.debug(`@htmlQuizzesList(.., ${curr}, ${total})`);

	// un élement <li></li> pour chaque quizz. Noter qu'on fixe une donnée
	// data-quizzid qui sera accessible en JS via element.dataset.quizzid.
	// On définit aussi .modal-trigger et data-target="id-modal-quizz-menu"
	// pour qu'une fenêtre modale soit affichée quand on clique dessus
	// VOIR https://materializecss.com/modals.html
	const quizzesLIst = quizzes.map(
	(q) =>
	  `<li class="collection-item cyan lighten-5" data-target="id-modal-quizz-menu" data-quizzid="${q.quiz_id}">
	    <h5>${q.title}</h5>
	    ${q.description} <a class="chip">${q.owner_id}</a>
	  </li>`
	);

  	// Si il n'y a qu'une page
  	// Alors on affiche pas de bouton
  	if(total === 1)
  	{
  		return `<ul class="collection">
				    ${quizzesLIst.join('')}
				</ul>`
  	}
  	else
  	{
  		// Création de la liste de bouton 
	  	let btnList = "";
		for(let i = 0; i<total; i++)
		{
			if(i+1 === curr)
			{
				btnList += `<li class="active"><a class="btnList" data-page="${i+1}">${i+1}</a></li>`;
			}
			else
			{
				btnList += `<li class="waves-effect"><a class="btnList" data-page="${i+1}">${i+1}</a></li>`
			}
		}
			
		// La liste complète et les deux boutons en bas
		const html = `
		<ul class="collection">
			${quizzesLIst.join('')}
		</ul>
		<div class="row">      
			<ul class="pagination">
			    ${(curr === 1) ? `<li class="disabled"><a><i class="material-icons">chevron_left</i></a></li>`
			    	: `<li class="waves-effect"><a id="id-prev-quizzes" data-page="${curr -
			      1}"><i class="material-icons">chevron_left</i></a></li>`
				 }
			    ${btnList}
			    ${(curr === total) ? `<li class="disabled"><a><i class="material-icons">chevron_right</i></a></li>`
			    	: `<li class="waves-effect"><a id="id-next-quizzes" data-page="${curr +
			      1}"><i class="material-icons">chevron_right</i></a></li>`
				 }
			</ul>
		</div>`;
		return html;
  	}
};

// //////////////////////////////////////////////////////////////////////////////
// RENDUS : mise en place du HTML dans le DOM et association des événemets
// //////////////////////////////////////////////////////////////////////////////

// met la liste HTML dans le DOM et associe les handlers aux événements
// eslint-disable-next-line no-unused-vars
function renderQuizzes() 
{
	console.debug(`@renderQuizzes()`);

	// les éléments à mettre à jour : le conteneur pour la liste des quizz
	const usersElt = document.getElementById('id-all-quizzes-list');
	// une fenêtre modale définie dans le HTML
	const modal = document.getElementById('id-modal-quizz-menu');

	// on appelle la fonction de généraion et on met le HTML produit dans le DOM
	usersElt.innerHTML = htmlQuizzesList(
	state.quizzes.results,
	state.quizzes.currentPage,
	state.quizzes.nbPages
	);

	// /!\ il faut que l'affectation usersElt.innerHTML = ... ait eu lieu pour
	// /!\ que prevBtn, nextBtn et quizzes en soient pas null
	// les éléments à mettre à jour : les boutons
	const prevBtn = document.getElementById('id-prev-quizzes');
	const nextBtn = document.getElementById('id-next-quizzes');
	const btnList = document.getElementsByClassName("btnList");
	// la liste de tous les quizzes individuels
	const quizzes = document.querySelectorAll('#id-all-quizzes-list>ul>li');

	// Ajout d'event change sur les select
	const selectLimit = document.getElementById("iptLimit");
	const selectOrder = document.getElementById("iptOrder");
	const selectDir = document.getElementById("iptDir");

	const changeSelect = () => 
	{
		getQuizzes(1, selectLimit.value, selectOrder.value, selectDir.value);
	}

	selectLimit.onchange = changeSelect;
	selectOrder.onchange = changeSelect;
	selectDir.onchange = changeSelect;

	// les handlers quand on clique sur "<" ou ">"
	function clickBtnPager() 
	{
	// remet à jour les données de state en demandant la page
	// identifiée dans l'attribut data-page
	// noter ici le 'this' QUI FAIT AUTOMATIQUEMENT REFERENCE
	// A L'ELEMENT AUQUEL ON ATTACHE CE HANDLER
		getQuizzes(this.dataset.page, selectLimit.value, selectOrder.value, selectDir.value);
	}

	if (prevBtn) prevBtn.onclick = clickBtnPager;
	if (nextBtn) nextBtn.onclick = clickBtnPager;
	if (btnList) Array.from(btnList).forEach(function(btn)
	{
		btn.onclick = clickBtnPager;
	});

	// qd on clique sur un quizz, on change sont contenu avant affichage
	// l'affichage sera automatiquement déclenché par materializecss car on
	// a définit .modal-trigger et data-target="id-modal-quizz-menu" dans le HTML
	function clickQuiz() 
	{
		// Si l'utilisateur est connecté
		if(state.user)
		{
			// Si on clique sur un autre quizz
			if(state.currentQuizz !== this.dataset.quizzid)
			{
				if(state.currentQuizz !== undefined)
		  		{
		  			// On met à jour le quizz courant
			  		state.currentQuizz = this.dataset.quizzid;
					console.debug(`@clickQuiz(${state.currentQuizz})`);

				    // On affiche la modal de warning
		  			const modal = document.getElementById("modal2");
		  			M.Modal.getInstance(modal).open();
		  			// Ajout d'un event click sur le bouton de la modal
		  			const ok = document.getElementById("continue");
		  			ok.onclick = renderCurrentQuizz;
		  		}
		  		else
		  		{
		  			// On met à jour le quizz courant
			  		state.currentQuizz = this.dataset.quizzid;
					console.debug(`@clickQuiz(${state.currentQuizz})`);

					// On affiche le quizz 
		  			renderCurrentQuizz();
		  		}
			}	
		}

		// Si l'utilsateur n'est pas connecté
		else 
		{
			M.toast({html: "Veuillez d'abord saisir votre X-API-KEY pour répondre aux quizzes."});
		}
	}

	// pour chaque quizz, on lui associe son handler
	quizzes.forEach((q) => 
	{
		q.onclick = clickQuiz;
	});
}

function renderCurrentQuizz() 
{
	const main = document.getElementById('id-all-quizzes-main');
	const addr = `${state.serverUrl}/quizzes/${state.currentQuizz}`;

	// On récupère (si quizz ouvert/existant) les questions/propositions du 
	// quizz pour l'affichage à l'aide d'un fetch 
	fetch(addr,
	{
		method: 'GET', 
		headers: state.headers()
	})
	.then(filterHttpResponse)
	.then((quizz) => 
	{
		// Si le quizz est ouvert
		if(quizz.open) 
		{
			fetch(`${addr}/questions`,
			{
				method: 'GET', 
				headers: state.headers()
			})
			.then(filterHttpResponse)
			.then((questions) => 
			{
			    let mainHtml = `<form id="form">`;
		        Array.from(questions).forEach(function(question)
		        {
					mainHtml += `<h5>${question.sentence}</h5>
					              <ol id="q-${question.question_id}">`;

					question.propositions.forEach(function(proposition)
					{
						mainHtml += `<li>
						              <label>
						                <input name="q-${question.question_id}" type="radio" id="p-${question.question_id}-${proposition.proposition_id}" class="with-gap"><span>${proposition.content}</span>
						              </label>
						            </li>`;
					});
					mainHtml += "</ol>";
		        });
		        // On ajout un bouton de validation
		        mainHtml += 
		        `<div class="row">	
		        	<button class="btn waves-effect waves-light" type="submit">Valider<i class="material-icons right">done</i></button>
		        	<button id="cancel-send" class="btn waves-effect waves-light red" type="button">Annuler<i class="material-icons right">cancel</i></button>
		        </div>`;

		        main.innerHTML = mainHtml + "</form>";
		        document.getElementById("form").onsubmit = submitQuizz;
		        document.getElementById("cancel-send").onclick = function()
		        {
		        	// On affiche la modal de warning
		  			const modal = document.getElementById("modal2");
		  			M.Modal.getInstance(modal).open();
		  			// Ajout d'un event click sur le bouton de la modal
		  			const ok = document.getElementById("continue");
		  			ok.onclick = function()
		  			{
		  				main.innerHTML = "";
		        		state.currentQuizz = undefined;
		  			};
		        }
		    });
		}
		// Si le requête ne donne rien
		else if(quizz.name === "NotFound")
		{
			M.toast({html: "Ce quizz n'existe pas."});
			document.getElementById('id-all-quizzes-main').innerHTML = "";
			state.currentQuizz = undefined;
		}
		// Si le quizz est fermé
		else 
		{
			M.toast({html: "Ce quizz est actuellement fermé."});
			document.getElementById('id-all-quizzes-main').innerHTML = "";
			state.currentQuizz = undefined;
		}
	});         
}

function submitQuizz(e)
{
	// Empêche le rechargement de la page
	e.preventDefault();

	const main = document.getElementById('id-all-quizzes-main');
	const ols = main.getElementsByTagName("ol");
	const quizz_id = parseInt(state.currentQuizz);

	// On parcours chaque question du quizz
	Array.from(ols).forEach(function(ol)
	{
		// On récupère l'id de la question et la réponse cochée
		// NB : l'id du ol est de sorte qu'on puisse faire l'opération ci-après
		const question_id = parseInt(ol.id.split("-")[1]);
		const p = ol.querySelector(`input:checked`);

		// Si l'utilisateur à répondu à la question
		// NB : Si l'utilisateur ne répond pas à une question
		// 		rien n'est envoyé sur le serveur
		if(p !== null)
		{
			// On récupère l'id de la réponse cochée
			const proposition_id = parseInt(p.id.split("-")[2]);

			// On envoie les réponses avec un fetch (methode POST)
			fetch(`https://lifap5.univ-lyon1.fr/quizzes/${quizz_id}/questions/${question_id}/answers/${proposition_id}`,
		    {
		    	method: "POST",
		    	headers: state.headers()
		    })
		    .then(filterAndDisplayHttpResponse)
		    .then(() =>
		    {
		    	main.innerHTML = "<p>Vos réponses ont été envoyé avec succès.</p>";
		    	state.currentQuizz = undefined;
		    })
		    .catch(() =>
		    {
		    	M.toast({html: "Une erreur est survenu lors de l'envoi de vos réponses."});
		    }); 
		}
	});
}

// Fonction qui renvoie le code HTML de la liste des quizzes de l'utilisateur
const htmlMyQuizzesList = (quizzes) => 
{
	console.debug(`@htmlQuizzesList(..)`);

	// un élement <li></li> pour chaque quizz. Noter qu'on fixe une donnée
	// data-quizzid qui sera accessible en JS via element.dataset.quizzid.
	// On définit aussi .modal-trigger et data-target="id-modal-quizz-menu"
	// pour qu'une fenêtre modale soit affichée quand on clique dessus
	// VOIR https://materializecss.com/modals.html
	const quizzesLIst = quizzes.map(
	(q) =>
	  `<li class="collection-item cyan lighten-5" data-target="id-modal-quizz-menu" data-quizzid="${q.quiz_id}">
	    <h5>${q.title}</h5>
	    ${q.description} <a class="chip">${q.owner_id}</a>
	  </li>`
	);


	// le bouton "+" pour ajouter un quizz
	const newBtn = `<button id="id-new-quizz" class="btn"><i class="material-icons">add_circle</i></button>`;

	// La liste complète et les deux boutons en bas
	const html = `
	<ul class="collection">
		${quizzesLIst.join('')}
	</ul>
	<div class="row">  
		<div class="col s6 left-align"></div>    
		<div class="col s6 right-align" onclick="clickAddQuizz()">${newBtn}</div>
	</div>
	`;
	return html;
};

// Fonction qui permet le rendu des quizzes crée par l'utilisateur
function renderUserQuizzes() 
{
	console.debug(`@renderUserQuizzes()`);

	// les éléments à mettre à jour : le conteneur pour la liste des quizz
	const usersElt = document.getElementById('id-my-quizzes-list');

	// on appelle la fonction de généraion et on met le HTML produit dans le DOM
	usersElt.innerHTML = htmlMyQuizzesList(state.userQuizzes);

	// la liste de tous les quizzes individuels
	const quizzes = document.querySelectorAll('#id-my-quizzes-list li');

	// qd on clique sur un quizz, on change sont contenu avant affichage
	// l'affichage sera automatiquement déclenché par materializecss car on
	// a définit .modal-trigger et data-target="id-modal-quizz-menu" dans le HTML
	function clickUserQuiz() 
	{
		const quizzId = this.dataset.quizzid;
		console.debug(`@clickUserQuiz(${quizzId})`);

		state.currentQuizz = quizzId;
		renderUserQuizz();
	}

	// pour chaque quizz, on lui associe son handler
	quizzes.forEach((q) => 
	{
		q.onclick = clickUserQuiz;
	});
}

// Fonction qui permet le rendu d'un quizz créé par l'utilisateur (dont l'id
// est state.currentQuizz)
function renderUserQuizz()
{
	const main = document.getElementById('id-my-quizzes-main');
	const addr = `${state.serverUrl}/quizzes/${state.currentQuizz}`;

	// On récupère les questions/propositions du quizz avec un fetch pour les
	// afficher
	fetch(`${addr}/questions`,
	{
		method: 'GET', 
		headers: state.headers()
	})
	.then(filterHttpResponse)
	.then(quizz =>
	{
		// On affiche le bouton d'édition du quizz
		let mainHtml = 
		`<div class="row">
			<button id="editQuizzBtn" class="btn waves-effect waves-light blue" type="button" name="action">Modifier les informations du quizz
			    <i class="material-icons right">edit</i>
			</button>
			<button id="delQuizzBtn" class="btn waves-effect waves-light red" type="button" name="action">Supprimer le quizz
			    <i class="material-icons right">delete</i>
			</button>
		</div>`;

		// On parcours chaque question du quizz
		Array.from(quizz).forEach(function(question)
		{
		  mainHtml += 
		  `<div class="divQuestUser row"><h5 id="q-${question.question_id}">
  			   	<span>
  			   		${question.sentence}
  			   	</span>
  			   	<span class="fixed-action-btn actionBtn">
				  <a class="btn-floating btn-medium green">
				    <i class="medium material-icons">menu</i>
				  </a>
				  <ul style="position: absolute; left: 3rem; top: 1rem;">
				  	<li><a class="btn-floating btn-small waves-effect waves-light delQuestionBtn red"><i class="material-icons">delete</i></a></li>
				    <li><a class="btn-floating btn-small waves-effect waves-light editQuestionBtn blue"><i class="material-icons">edit</i></a></li>
				  </ul>
				</span>
  			   	</h5>
			</div>
            <ol>`;

		  question.propositions.forEach(function(proposition)
		  {
		    mainHtml += 
		    	`<li id="p-${question.question_id}-${proposition.proposition_id}">${proposition.content}</li>`;
		  });
		  mainHtml += 
		  "</ol>";
		});
		main.innerHTML = mainHtml;

		// On affiche le bouton d"ajout de questions
		main.innerHTML += 
		`<div class="row">
			<button id="addQuestionBtn" class="btn waves-effect waves-light" type="button" name="action">Ajouter une question
			    <i class="material-icons right">add</i>
			</button>
		</div>`;

		// Initialisation du "Floatin Action Button"
		const elems = document.querySelectorAll('.fixed-action-btn');
	    const instances = M.FloatingActionButton.init(elems, {
	      direction: 'right'
	    });

		// Ajout d'event click sur les boutons
		document.getElementById("addQuestionBtn").onclick = clickAddQuestion;
		document.getElementById("editQuizzBtn").onclick = clickEditQuizz;
		document.getElementById("delQuizzBtn").onclick = clickDelQuizz;
		Array.from(document.getElementsByClassName("editQuestionBtn")).forEach(function(button)
		{
			button.onclick = clickEditQuestion;
		});
		Array.from(document.getElementsByClassName("delQuestionBtn")).forEach(function(button)
		{
			button.onclick = clickDelQuestion;
		});
	})
	.catch(function()
	{
		main.innerHTML = "";
		M.toast({html: `Le quizz ${state.currentQuizz} est introuvable.`});
		state.currentQuizz = undefined;
	});
}

const clickAddQuizz = () => 
{
	// Indique que l'utilisateur est en train d'ajouter un quizz
	state.use = 1;
	state.currentQuizz = undefined;

	// Ajout du formulaire d'ajout de quizz
	const main = document.getElementById('id-my-quizzes-main');
	main.innerHTML = 
	`<div class="row">
		<h4 class="center">Création d'un quizz</h4>
	    <form id="form-add" class="col s12">
			<div class="switch">
			    <label>
			      Fermé
			      <input id="open" type="checkbox">
			      <span class="lever"></span>
			      Ouvert
			    </label>
			</div>
			<div class="row">
				<div class="input-field col s6">
				  <input id="title" type="text" class="validate" required>
				  <label for="title">Titre</label>
				</div>
				<div class="input-field col s6">
				  <input id="description" type="text" class="validate" required>
				  <label for="description">Description</label>
				</div>
				<div class="row">
					<div class="col s12 right-align">
						<button class="btn waves-effect waves-light" type="submit" name="action">Créer le quizz
						    <i class="material-icons right">add</i>
						</button>
						<button id="cancelAddQuizz" class="btn waves-effect waves-light red" type="button" name="action">Annuler
						    <i class="material-icons right">cancel</i>
						</button>
					</div>
				</div>
			</div>
	   </form>
  </div>`;

  // Ajout de l'event submit sur le bouton de validation
  document.getElementById('form-add').onsubmit = submitAddQuizz;

  // Ajout de l'event click sur le bouton d'annulation
  document.getElementById('cancelAddQuizz').onclick = function()
  {
  	main.innerHTML = "";
	state.use = 0;
  };
}

const clickAddQuestion = () => 
{
	// Indique que l'utilisateur est en train d'ajouter un question
	state.use = 4;

	// Affichage du formulaire d'ajout du question
	const main = document.getElementById('id-my-quizzes-main');
	main.innerHTML = 
	`<div class="row">
		<h4 class="center">Ajout d'une question au quizz ${state.currentQuizz}</h4>
	    <form id="form-add" class="col s12">
			<div class="row">
				<div class="input-field col s6">
					<input id="sentence" type="text" class="validate" required>
					<label for="sentence">Question</label>
				</div>
			</div>
			<div class="row">
				<div class="input-field col s6">
					<input id="prop-1" type="text" class="validate" required>
					<label for="prop-1">Proposition 1</label>
				</div>
				<div class="input-field col s6 switch">
				    <label>
				      Faux
				      <input id="c-1" type="checkbox">
				      <span class="lever"></span>
				      Correct
				    </label>
				</div>
			</div>
			<div class="row">
				<div class="input-field col s6">
					<input id="prop-2" type="text" class="validate" required>
					<label for="prop-2">Proposition 2</label>
				</div>
				<div class="input-field col s6 switch">
				    <label>
				      Faux
				      <input id="c-2" type="checkbox">
				      <span class="lever"></span>
				      Correct
				    </label>
				</div>
			</div>
			<div class="row">
				<div class="input-field col s6">
					<input id="prop-3" type="text" class="validate">
					<label for="prop-3">Proposition 3</label>
				</div>
				<div class="input-field col s6 switch">
				    <label>
				      Faux
				      <input id="c-3" type="checkbox">
				      <span class="lever"></span>
				      Correct
				    </label>
				</div>
			</div>
			<div class="row">
				<div class="input-field col s6">
					<input id="prop-4" type="text" class="validate">
					<label for="prop-4">Proposition 4</label>
				</div>
				<div class="input-field col s6 switch">
				    <label>
				      Faux
				      <input id="c-4" type="checkbox">
				      <span class="lever"></span>
				      Correct
				    </label>
				</div>
			</div>
			<div class="row">
				<div class="col s12 right-align">
					<button class="btn waves-effect waves-light" type="submit" name="action">Ajouter la question
					    <i class="material-icons right">add</i>
					</button>
					<button id="cancelAddQuestion" class="btn waves-effect waves-light red" type="button" name="action">Annuler
					    <i class="material-icons right">cancel</i>
					</button>
				</div>
			</div>
	    </form>
  </div>`;

  // Ajout de l'event submit sur le bouton de validation
  document.getElementById('form-add').onsubmit = submitAddQuestion;

  // Ajout de l'event click sur le bouton d'annulation
  document.getElementById('cancelAddQuestion').onclick = function()
  {
  	main.innerHTML = "";
  	state.use = 0;
  	renderUserQuizz();
  };
}

const clickEditQuizz = () =>
{
	// Indique que l'utilisateur est en train d'éditer un quizz
  	state.use = 2;

	// On affiche le formulaire d'édition de quizz (vide)
	const main = document.getElementById('id-my-quizzes-main');
	main.innerHTML = 
	`<div class="row">
		<h4 class="center">Modification du quizz ${state.currentQuizz}</h4>
	    <form id="form-edit" class="col s12">
			<div class="switch">
			    <label>
			      Fermé
			      <input id="open" type="checkbox">
			      <span class="lever"></span>
			      Ouvert
			    </label>
			</div>
			<div class="row">
				<div class="input-field col s6">
				  <input id="title" type="text" class="validate" required>
				  <label for="title" class="active">Titre</label>
				</div>
				<div class="input-field col s6">
				  <input id="description" type="text" class="validate" required>
				  <label for="description" class="active">Description</label>
				</div>
				<div class="row">
					<div class="col s12 right-align">
						<button class="btn waves-effect waves-light" type="submit" name="action">Modifier le quizz
						    <i class="material-icons right">edit</i>
						</button>
						<button id="cancelEditQuizz" class="btn waves-effect waves-light red" type="button" name="action">Annuler
						    <i class="material-icons right">cancel</i>
						</button>
					</div>
				</div>
			</div>
	    </form>
  </div>`;

  // On remplie le formulaire avec les données du quizz sélectionné
  const addr = `${state.serverUrl}/quizzes/${state.currentQuizz}`;
  fetch(addr,
  {
	method: 'GET', 
	headers: state.headers()
  })
  .then(filterHttpResponse)
  .then( (quizz) => 
  {
  	document.getElementById("open").checked = quizz.open;
  	document.getElementById("title").value = quizz.title;
  	document.getElementById("description").value = quizz.description;
  });	

  // On ajoute un event "submit" pour envoyer les modifications sur le serveur
  document.getElementById('form-edit').onsubmit = submitEditQuizz;	

  // Ajout de l'event click sur le bouton d'annulation
  document.getElementById('cancelEditQuizz').onclick = function()
  {
  	main.innerHTML = "";
  	state.use = 0;
  	renderUserQuizz();
  };
}

const clickEditQuestion = (e) =>
{
	// Indique que l'utilisateur est en train d'éditer une question
  	state.use = 5;

	// On récupère l'id de la question et la question et les réponses qui correspond
	const questionId = parseInt(e.target.parentElement.parentElement.parentElement.parentElement.parentElement.id.split("-")[1]);
	const sentence = document.getElementById(`q-${questionId}`).firstElementChild;
	const ol = document.getElementsByTagName('ol')[questionId];
	const nbProp = ol.childElementCount;

	// Affichage du formulaire d'édition de la question
	const main = document.getElementById('id-my-quizzes-main');
	let html = 
	`<h4 class="center">Modification de la question ${questionId+1} du quizz ${state.currentQuizz}</h4>
	<form id="form-edit-question">
		<div class="row">
			<div class="input-field col s6">
				<input id="sentence" class="${questionId}" type="text" class="validate" value="${sentence.innerText}" required>
				<label for="sentence" class="active">Question</label>
			</div>
		</div>`;

	Array.from(ol.children).forEach(function(prop, i)
	{
		html += 
		`<div class="row">
			<div class="input-field col s6">
				<input id="prop-${i+1}" type="text" class="validate" value="${prop.innerHTML}" required>
				<label for="prop-${i+1}" class="active">Proposition ${i+1}</label>
			</div>
			<div class="input-field col s6 switch">
			    <label>
			      Faux
			      <input id="c-${i+1}" type="checkbox">
			      <span class="lever"></span>
			      Correct
			    </label>
			</div>
		</div>`;
	});

	html +=
		`<div class="row">
			<div class="col s12 right-align">
				<button id="validEditQuestionBtn" class="btn waves-effect waves-light" type="submit" name="action">Modifier la question
				    <i class="material-icons right">edit</i>
				</button>
				<button id="cancelEditQuestion" class="btn waves-effect waves-light red" type="button" name="action">Annuler
				    <i class="material-icons right">cancel</i>
				</button>
			</div>
		</div>
	</form>`;

	main.innerHTML = html;

  // On effectue un fetch pour récupérer la bonne réponse
  fetch(`${state.serverUrl}/quizzes/${state.currentQuizz}/questions/${questionId}`,
  {
	method: 'GET', 
	headers: state.headers()
  })
  .then(filterHttpResponse)
  .then(function(question)
  {
  	document.getElementById(`c-${question.correct_propositions_number}`).checked = true;
  });

  document.getElementById("form-edit-question").onsubmit = submitEditQuestion;

  // Ajout de l'event click sur le bouton d'annulation
  document.getElementById('cancelEditQuestion').onclick = function()
  {
  	main.innerHTML = "";
  	state.use = 0;
  	renderUserQuizz();
  };
}

const clickDelQuestion = (e) =>
{
	// Indique que l'utilisateur est en train de supprimer une question
	state.use = 6

	// On récupère l'id de la question et la question et les réponses qui correspond
	const questionId = parseInt(e.target.parentElement.parentElement.parentElement.parentElement.parentElement.id.split("-")[1]);

	// On affiche la modal de suppression
	const modal = document.getElementById("modal3");
	M.Modal.getInstance(modal).open();

	// Ajout d'un event click sur le bouton de la modal
	const ok = document.getElementById("valid-del-quest");
	ok.onclick = submitDelQuestion(questionId);
	const cancel = document.getElementById("cancel-del-quest");
	cancel.onclick = () =>
	{
		state.use = 0;
	};
}

const clickDelQuizz = () =>
{
	// Indique que l'utilisateur est en train de supprimer un quizz
	state.use = 3;

	// On affiche la modal de suppression
	const modal = document.getElementById("modal4");
	M.Modal.getInstance(modal).open();

	// Ajout d'un event click sur le bouton de la modal
	const ok = document.getElementById("valid-del-quizz");
	ok.onclick = submitDelQuizz;
	const cancel = document.getElementById("cancel-del-quizz");
	cancel.onclick = () =>
	{
		state.use = 0;
	};
} 

const submitAddQuizz = (e) =>
{
	// Empêche le rechargement de la page
	e.preventDefault();

	// Création d'un objet de type FormData pour stocker les saisies
	const formData = new FormData();
	formData.append("title", `${document.getElementById('title').value}`);
	formData.append("description", `${document.getElementById('description').value}`);
	formData.append("open", document.getElementById('open').checked);

	// Création de l'objet JSON (à partir du FormData) à envoyer sur le serveur
	const jsonData = {};
	for (const pair of formData.entries())
	{
		jsonData[`${pair[0]}`] = pair[1];
	}

	// Envoie des données avec fetch(url) (methode POST)
	fetch(`${state.serverUrl}/quizzes`, 
	{
		method: "POST",
    	headers: state.headers(),
		body: JSON.stringify(jsonData)
	})
	.then(filterAndDisplayHttpResponse)
	.then(function(response)
	{
		state.currentQuizz = response.quiz_id;
		document.getElementById("id-my-quizzes-main").innerHTML = "";
	})
	.catch(function()
	{
		M.toast({html: "Erreur lors de la création du quizz."});
	});
}

const submitEditQuizz = (e) => 
{
	// Empêche la rechargement de la page
	e.preventDefault();

	// Création d'un objet de type FormData pour stocker les saisies
	const formData = new FormData();
	formData.append("title", `${document.getElementById('title').value}`);
	formData.append("description", `${document.getElementById('description').value}`);
	formData.append("open", document.getElementById('open').checked);

	// Création de l'objet JSON (à partir du FormData) à envoyer sur le serveur
	const jsonData = {};
	for (const pair of formData.entries())
	{
		jsonData[`${pair[0]}`] = pair[1];
	}

	// Envoie des données avec fetch(url) (methode PUT)
	fetch(`${state.serverUrl}/quizzes/${state.currentQuizz}`, 
	{
		method: "PUT",
    	headers: state.headers(),
		body: JSON.stringify(jsonData)
	})
	.then(filterAndDisplayHttpResponse)
	.then(function()
	{
		document.getElementById("id-my-quizzes-main").innerHTML = "";
	})
	.catch(function()
	{
		M.toast({html: "Erreur lors de la modification du quizz."});
	});
}

const submitAddQuestion = (e) =>
{
	// Empêche le rechargement de la page
	e.preventDefault();
	
	// Création d'un objet de type FormData pour stocker les saisies
	const formData = new FormData();

	// On "récupère" par un fetch (methode GET) le questionId
	// NB : le questionId de la question à créé est en fait la
	// valeur questions_number
	fetch(`${state.serverUrl}/quizzes/${state.currentQuizz}`,
	{
		method: 'GET', 
		headers: state.headers()
	})
	.then(filterHttpResponse)
	.then(function(quizz)
	{
		formData.append("question_id", quizz.questions_number);
		formData.append("sentence", `${document.getElementById('sentence').value}`);

		// Les 2 premières propositions sont toujours remplies
		let propositions = [
		{
			"content": `${document.getElementById('prop-1').value}`,
			"proposition_id": 0,
			"correct": document.getElementById('c-1').checked
	  	},
	  	{
			"content": `${document.getElementById('prop-2').value}`,
			"proposition_id": 1,
			"correct": document.getElementById('c-2').checked
	  	}];

	  	// On récupère les 2 autres propositions si elles sont remplies
		if(document.getElementById('prop-3').value != "")
		{
			const p = 
			{
				"content": `${document.getElementById('prop-3').value}`,
				"proposition_id": 2,
				"correct": document.getElementById('c-3').checked
		  	}
			propositions.push(p);
		}
		if(document.getElementById('prop-4').value != "")
		{
			const p = 
			{
				"content": `${document.getElementById('prop-4').value}`,
				"proposition_id": 3,
				"correct": document.getElementById('c-4').checked
		  	}
			propositions.push(p);
		}
		
		// Création de l'objet JSON (à partir du FormData) à envoyer sur le serveur
		const jsonData = {};
		for (const pair of formData.entries())
		{
			jsonData[`${pair[0]}`] = pair[1];
		}
		jsonData["propositions"] = propositions;

		// Envoie les données de la question avec fetch (methode POST)
		fetch(`${state.serverUrl}/quizzes/${state.currentQuizz}/questions`, 
		{
			method: "POST",
	    	headers: state.headers(),
			body: JSON.stringify(jsonData)
		})
		.then(filterAndDisplayHttpResponse)
		.then(function()
		{
			document.getElementById("id-my-quizzes-main").innerHTML = "";
		})
		.catch(function()
		{
			M.toast({html: "Erreur lors de l'ajout de la question."});
		});
	});

}

const submitEditQuestion = (e) => 
{
	// Empêche le rechargement de la page
	e.preventDefault();
	
	// Création d'un objet de type FormData pour stocker les saisies
	const formData = new FormData();
	const questionId = document.getElementById("sentence").classList[0];

	formData.append("sentence", `${document.getElementById('sentence').value}`);

	// Les 2 premières propositions sont toujours remplies
	let propositions = [
	{
		"content": `${document.getElementById('prop-1').value}`,
		"proposition_id": 0,
		"correct": document.getElementById('c-1').checked
  	},
  	{
		"content": `${document.getElementById('prop-2').value}`,
		"proposition_id": 1,
		"correct": document.getElementById('c-2').checked
  	}];

  	// On récupère les 2 autres propositions si elles existent
	if(document.getElementById('prop-3') != null)
	{
		const p = 
		{
			"content": `${document.getElementById('prop-3').value}`,
			"proposition_id": 2,
			"correct": document.getElementById('c-3').checked
	  	}
		propositions.push(p);
	}
	if(document.getElementById('prop-4') != null)
	{
		const p = 
		{
			"content": `${document.getElementById('prop-4').value}`,
			"proposition_id": 3,
			"correct": document.getElementById('c-4').checked
	  	}
		propositions.push(p);
	}
	
	// Création de l'objet JSON (à partir du FormData) à envoyer sur le serveur
	const jsonData = {};
	for (const pair of formData.entries())
	{
		jsonData[`${pair[0]}`] = pair[1];
	}
	jsonData["propositions"] = propositions;

	// Envoie les données de la question avec fetch (methode POST)
	fetch(`${state.serverUrl}/quizzes/${state.currentQuizz}/questions/${questionId}`, 
	{
		method: "PUT",
    	headers: state.headers(),
		body: JSON.stringify(jsonData)
	})
	.then(filterAndDisplayHttpResponse)
	.then(function()
	{
		document.getElementById("id-my-quizzes-main").innerHTML = "";
	})
	.catch(function()
	{
		M.toast({html: "Erreur lors de l'édition de la question."});
	});
}

const submitDelQuestion = (questionId) => () =>
{
	// On envoie la requête de suppression au serveur avec un fetch (methode DELETE)
	fetch(`${state.serverUrl}/quizzes/${state.currentQuizz}/questions/${questionId}`,
	{
		method: "DELETE",
    	headers: state.headers()
	})
	.then(filterAndDisplayHttpResponse)
	.then( () => 
	{
		document.getElementById("id-my-quizzes-main").innerHTML = "";
	})
	.catch( () => 
	{
		M.toast({html: "Une erreur est survenu lors de la suppression de la question."});
	});
}

const submitDelQuizz = () => 
{
	// On envoie la requête de suppression au serveur avec un fetch (methode DELETE)
	fetch(`${state.serverUrl}/quizzes/${state.currentQuizz}`,
	{
		method: "DELETE",
    	headers: state.headers()
	})
	.then(filterAndDisplayHttpResponse)
	.then( () => 
	{
		document.getElementById("id-my-quizzes-main").innerHTML = "";
		state.currentQuizz = undefined;
	})
	.catch( () => 
	{
		M.toast({html: "Une erreur est survenu lors de la suppression du quizz."});
	});
}

// Fonction de rendu des réponses de l'utilisateur
function renderUserAnswers() 
{
	console.debug(`@renderUserAnswers()`);

	// les éléments à mettre à jour : le conteneur pour la liste des quizz
	const usersElt = document.getElementById('id-my-answers-list');

	// on appelle la fonction de généraion et on met le HTML produit dans le DOM
	usersElt.innerHTML = htmlQuizzesList(state.userAnswers,1,1);

	// la liste de tous les quizzes individuels
	const quizzes = document.querySelectorAll('#id-my-answers-list li');

	// qd on clique sur un quizz, on change sont contenu avant affichage
	// l'affichage sera automatiquement déclenché par materializecss car on
	// a définit .modal-trigger et data-target="id-modal-quizz-menu" dans le HTML
	function clickUserAnswer() 
	{
		const quizzId = this.dataset.quizzid;
		console.debug(`@clickUserAnswer(${quizzId})`);

		// eslint-disable-next-line no-use-before-define
		state.currentQuizz = quizzId;
		renderUserAnswer();
	}

	// pour chaque quizz, on lui associe son handler
	quizzes.forEach((q) => 
	{
		q.onclick = clickUserAnswer;
	});
}

function renderUserAnswer()
{
	const main = document.getElementById('id-my-answers-main');
	const addr = `${state.serverUrl}/quizzes/${state.currentQuizz}`;

	// On récupère et affiche les réponses au quizz avec un fetch 
	fetch(`${addr}/questions`,
	{
		method: 'GET', 
		headers: state.headers()
	})
	.then(filterHttpResponse)
	.then(quizz =>
	{
		let mainHtml = `<form>`;

		// On parcours chaque questions du quizz
		Array.from(quizz).forEach(function(question)
		{

			mainHtml += `<h5>${question.sentence}</h5>
			              <ol id="q-${question.question_id}">`;
			// On parcours chaque proposition de la question
			question.propositions.forEach(function(proposition)
			{
				mainHtml += `<li>
				              <label>
				                <input name="q-${question.question_id}" type="radio" id="a-${question.question_id}-${proposition.proposition_id}" class="with-gap" disabled="disabled">
				                <span>${proposition.content}</span>
				              </label>
				            </li>`;
			});
			mainHtml += "</ol>";
		});
		main.innerHTML = mainHtml + "</form>";

		// On coche avec les réponses récupérées sur le serveur
		Array.from(state.userAnswers).forEach(function(quiz)
		{
			if(quiz.quiz_id == state.currentQuizz)
			{
				quiz.answers.forEach(function(answer)
				{
					document.getElementById(`a-${answer.question_id}-${answer.proposition_id}`).checked = true;
				});
			}
		});
	});
}

const clickAllQuizzes = () =>
{
	// Si on vient de la section "Mes quizz" ou "Mes réponses"
	if(state.section !== 0)
	{
		state.currentQuizz = undefined;
	}
	state.section = 0;
}
const clickMyQuizzes = () =>
{
	// Si on est en train de répondre à quizz 
	if(state.currentQuizz !== undefined && state.section === 0)
	{
		// On empêche le changement de section
		// NB : l'utilisation de preventDefault ne fonctionne pas
		// sur les "tab" de Materialize (que ce soit sur les <a> ou <li>)
		// d'où l'utilisation de cette méthode
		const tabs = document.getElementsByClassName("tabs")[0];
		const instance = M.Tabs.getInstance(tabs);
		setTimeout(function()
		{
			instance.select('id-all-quizzes');
		}, 100);

		// On affiche la modal de warning
		const modal = document.getElementById("modal2");
		M.Modal.getInstance(modal).open();

		// Ajout d'un event click sur le bouton de la modal
		const ok = document.getElementById("continue");
		ok.onclick = function()
		{
			// On change de section
			setTimeout(function()
			{
				instance.select('id-my-quizzes');
			}, 100);

			// On appelle le rendu de la section "Mes quizzes"
			loadMyQuizzesSection();
		};
	}

	else
	{
		loadMyQuizzesSection();
	}
}

const clickMyAnswers = () =>
{
	// Si on est en train de répondre à quizz 
	if(state.currentQuizz !== undefined && state.section === 0)
	{
		// On empêche le changement de section
		const tabs = document.getElementsByClassName("tabs")[0];
		const instance = M.Tabs.getInstance(tabs);
		setTimeout(function()
		{
			instance.select('id-all-quizzes');
		}, 100);

		// On affiche la modal de warning
		const modal = document.getElementById("modal2");
		M.Modal.getInstance(modal).open();

		// Ajout d'un event click sur le bouton de la modal
		const ok = document.getElementById("continue");
		ok.onclick = function()
		{
			// On change de section
			setTimeout(function()
			{
				const tabs = document.getElementsByClassName("tabs")[0];
				const instance = M.Tabs.getInstance(tabs);
				instance.select('id-my-answers');
			}, 100);

			// On appelle le rendu de la section "Mes Réponses"
			loadMyAnswersSection();
		};
	}
	else
	{
		loadMyAnswersSection();
	}
}

const loadMyQuizzesSection = () =>
{
	// Remet à zéro la section "Tous les quizz"
	document.getElementById("id-all-quizzes-main").innerHTML = "";
	state.currentQuizz = undefined;

	// Remet à zéro l'affichage de la section "Mes Quizz"
	document.getElementById("id-my-quizzes-main").innerHTML = "";

	// Si l'utilisateur est connecté
	if(state.user)
	{
		getUserQuizzes().then(function()
		{
			renderUserQuizzes();
		});	
	}

	else
	{
		document.getElementById("id-my-quizzes-list").innerHTML = "";
		M.toast({html: "Veuillez d'abord saisir votre X-API-KEY."});
	}

	state.section = 1;
}

const loadMyAnswersSection = () => 
{
	// Remet à zéro la section "Tous les quizz"
	document.getElementById("id-all-quizzes-main").innerHTML = "";
	state.currentQuizz = undefined;

	// Remet à zéro l'affichage de la section "Mes Réponses"
	document.getElementById("id-my-answers-main").innerHTML = "";

	// Si l'utilisateur est connecté
	if(state.user)
	{
		getUserAnswers().then(function()
		{
			renderUserAnswers();
		});
	}
	else
	{
		document.getElementById("id-my-answers-list").innerHTML = "";
		M.toast({html: "Veuillez d'abord saisir votre X-API-KEY."});
	}
	
	state.section = 2;
}

document.getElementById("id-all-quizzes-tab").onclick = clickAllQuizzes;
document.getElementById("id-my-quizzes-tab").onclick = clickMyQuizzes;
document.getElementById("id-my-answers-tab").onclick = clickMyAnswers;

const displayHttpResponse = (response) => 
{
	if(response.status === 200 || response.status === 201)
    {
        // Ajout de quizz
        if(state.use === 1)
        {
          M.toast({html: "Le quizz a été ajouter avec succès."});
        }

        // Modification de quizz
        else if(state.use === 2)
        {
          M.toast({html: "Le quizz a été modifier avec succès."});
        }

        // Suppresion de quizz
        else if(state.use === 3)
        {
          M.toast({html: "La quizz a été supprimer avec succès."});
        }

        // Ajout de question
        else if(state.use === 4)
        {
          M.toast({html: "La question a été ajouter avec succès."});
        }

        // Modification de question
        else if(state.use === 5)
        {
          M.toast({html: "La question a été modifier avec succès."});
        }

        // Suppresion de question
        else if(state.use === 6)
        {
          M.toast({html: "La question a été supprimer avec succès."});
        }
    }
	// Les deux cas ci-dessous ne sont en théorie pas possible
	// 1 - La clé est vérifié dès la connexion
	// 2 - Les fonctionnalités de modification/suppression sont disponible
	// uniquement dans la section "Mes quizzes" qui contient uniquement les
	// quizz de l'utilisateur
	else if(response.status === 401)
	{
		M.toast({html: "Votre X-API-KEY est invalide."});
	}
	else if(response.status === 403)
	{
		M.toast({html: "Vous n'êtes pas le propriétaire de cette ressource."});
	}
	else if(response.status === 404)
	{
		// Modification de quizz
		if(state.use === 2)
		{
		  M.toast({html: "Ce quizz est introuvable."});
		}

		// Modification de question
		// Suppresion de question
		else if(state.use === 4 || state.use === 5)
		{
		  M.toast({html: "Cette question est introuvable."});
		}
	}
}

// eslint-disable-next-line no-unused-vars
const renderUserBtn = () => 
{
	const btn = document.getElementById('id-login');
	btn.onclick = () => 
	{
		// Si l'utilisateur est déjà connecté
		if(state.user) 
		{
		  // eslint-disable-next-line no-alert
		  document.getElementById('logContent').innerHTML = 
		  `<p>Bonjour ${state.user.firstname} ${state.user.lastname.toUpperCase()}, voulez-vous vous déconnecter ?<p>`;

		  const logOut = document.getElementById('log');
		  logOut.innerText = "Se déconnecter";
		  document.getElementById('titleLog').innerText = "Déconnexion";
		  
		  logOut.onclick = () =>
		  {
		  	resetState();
		    document.getElementById('id-all-quizzes-main').innerHTML = "";
		    document.getElementById('id-my-quizzes-main').innerHTML = "";
		    document.getElementById('id-my-quizzes-list').innerHTML = "";
		    document.getElementById('id-my-answers-main').innerHTML = "";
		    document.getElementById('id-my-answers-list').innerHTML = "";
		    btn.innerText = "account_circle";
		    M.toast({html: 'Déconnexion réussi !'});
		  }
		}
	 
		// Si l'utilisateur n'est pas connecté
		else 
		{
		  // eslint-disable-next-line no-alert
		  const logContent = document.getElementById('logContent');
		  logContent.innerHTML = `<div class="input-field col s12">
		      <input id="xApiKey" name="xApiKey" type="text" class="validate">
		      <label for="xApiKey">X-API-KEY</label>
		    </div>`;
		  
		  const logIn = document.getElementById('log');
		  logIn.innerText = "Se connecter";
		  logIn.onclick = () =>
		  {
		  	state.xApiKey = document.getElementById('xApiKey').value;
		  	getUser().then(function()
		  	{
		  		// Si la connexion a réussi
		  		if(state.user)
				{
					M.toast({html: 'Connexion réussi !'});
					btn.innerText = "exit_to_app";
					getUserQuizzes();
					getUserAnswers();
				}
				else
				{
					M.toast({html: 'Erreur lors de la connexion.'});
				}
		  	});
		  }
		}
	};
};
