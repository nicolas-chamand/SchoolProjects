/* globals renderQuizzes renderUserBtn */

// //////////////////////////////////////////////////////////////////////////////
// LE MODELE, a.k.a, ETAT GLOBAL
// //////////////////////////////////////////////////////////////////////////////

// un objet global pour encapsuler l'état de l'application
// on pourrait le stocker dans le LocalStorage par exemple
const state = 
{
  // la clef de l'utilisateur
  xApiKey: '', //cfbba9d6-4b7a-4e37-a3f3-0c7455164f0c

  // l'URL du serveur où accéder aux données
  serverUrl: 'https://lifap5.univ-lyon1.fr',

  // la liste des quizzes
  quizzes: [],

  // le quizz actuellement choisi
  currentQuizz: undefined,

  headers()
  {
    const headers = new Headers();
    headers.set('X-API-KEY', this.xApiKey);
    headers.set('Accept', 'application/json');
    headers.set('Content-Type', 'application/json');
    return headers;
  }, 

  // Entier qui définit dans quel section on se trouve
  // 0 pour la section "Tous les quizz"
  // 1 pour la section "Mes quizz"
  // 2 pour la section "Mes réponses"
  section: 0,

  // Entier qui indique quel fonctionnalité est en cours (section "Mes quizz")
  // 0 pour aucune/visualisation des quizzes
  // 1 pour ajout de quizzes
  // 2 pour modification de quizzes
  // 3 pour ajout de questions
  // 4 pour modification de questions
  // 5 pour suppresion de quizzes
  // Permet la gestion/affichage des erreurs et la gestion de mise à jour
  // de l'interface
  use: 0
};

// une méthode pour l'objet 'state' qui va générer les headers pour les appel à fetch


// //////////////////////////////////////////////////////////////////////////////
// OUTILS génériques
// //////////////////////////////////////////////////////////////////////////////

// un filtre simple pour récupérer les réponses HTTP qui correspondent à des
// erreurs client (4xx) ou serveur (5xx)
// Utilisé principalement pour les fetch en mode GET
// eslint-disable-next-line no-unused-vars
function filterHttpResponse(response) 
{
  return response
  .json()
  .then((data) => 
  {
    if (response.status >= 400 && response.status < 600) 
    {
      throw new Error(`${data.name}: ${data.message}`);
    }
    return data;
  })
  .catch((err) => console.error(`Error on json: ${err}`));
}

// Un filtre plus avancé pour les fonctionnalités POST/PUT/DELETE des quizzes
// et questions
function filterAndDisplayHttpResponse(response) 
{
  return response
  .json()
  .then((data) => 
  {
    displayHttpResponse(response);
    state.use = 0;
    return data;
  })
  .catch((err) => console.error(`Error on json: ${err}`));
}

// //////////////////////////////////////////////////////////////////////////////
// DONNEES DES UTILISATEURS
// //////////////////////////////////////////////////////////////////////////////

// mise-à-jour asynchrone de l'état avec les informations de l'utilisateur
// l'utilisateur est identifié via sa clef X-API-KEY lue dans l'état
// eslint-disable-next-line no-unused-vars
const getUser = () => 
{
  console.debug(`@getUser()`);
  const url = `${state.serverUrl}/users/whoami`;
  return fetch(url, { method: 'GET', headers: state.headers() })
  .then(filterHttpResponse)
  .then((data) => 
  {
    // /!\ ICI L'ETAT EST MODIFIE /!\
    state.user = data;
    // on lance le rendu du bouton de login
    return renderUserBtn();
  });
};

// //////////////////////////////////////////////////////////////////////////////
// DONNEES DES QUIZZES
// //////////////////////////////////////////////////////////////////////////////

// mise-à-jour asynchrone de l'état avec les informations de l'utilisateur
// getQuizzes télécharge la page 'p' des quizzes et la met dans l'état
// puis relance le rendu
// eslint-disable-next-line no-unused-vars
const getQuizzes = (p = 1, limit = 50, order = "quiz_id", dir = "asc") => 
{
  console.debug(`@getQuizzes(${p})`);
  const url = `${state.serverUrl}/quizzes/?page=${p}&limit=${limit}&order=${order}&dir=${dir}`;

  // le téléchargement est asynchrone, là màj de l'état et le rendu se fait dans le '.then'
  return fetch(url, { method: 'GET', headers: state.headers() })
  .then(filterHttpResponse)
  .then((data) => 
  {
    // /!\ ICI L'ETAT EST MODIFIE /!\
    state.quizzes = data;

    // on a mis à jour les donnés, on peut relancer le rendu
    // eslint-disable-next-line no-use-before-define
    return renderQuizzes();
  });
};


const getUserQuizzes = () => 
{
  console.debug(`@getUserQuizzes()`);
  const url = `${state.serverUrl}/users/quizzes`;

  // le téléchargement est asynchrone, là màj de l'état et le rendu se fait dans le '.then'
  return fetch(url, { method: 'GET', headers: state.headers() })
  .then(filterHttpResponse)
  .then((data) => 
  {
    // /!\ ICI L'ETAT EST MODIFIE /!\
    state.userQuizzes = data;

    // on a mis à jour les donnés, on peut relancer le rendu
    // eslint-disable-next-line no-use-before-define
    return renderUserQuizzes();
  });
};

const getUserAnswers = () => 
{
  console.debug(`@getUserAnswers()`);
  const url = `${state.serverUrl}/users/answers`;

  // le téléchargement est asynchrone, là màj de l'état et le rendu se fait dans le '.then'
  return fetch(url, { method: 'GET', headers: state.headers() })
  .then(filterHttpResponse)
  .then((data) => 
  {
    // /!\ ICI L'ETAT EST MODIFIE /!\
    state.userAnswers = data;

    // on a mis à jour les donnés, on peut relancer le rendu
    // eslint-disable-next-line no-use-before-define
    return renderUserAnswers();
  });
};

const resetState = () => 
{
  state.xApiKey = undefined;
  state.user = undefined;
  state.currentQuizz = undefined;
  state.userQuizzes = undefined;
  state.userAnswers = undefined;
}

const refreshPage = (e) => 
{
  console.log(`callBack : ${e}`);
  // On recharge la page et les affichages seulement si l'utilisateur est
  // connecté
  if(state.user) 
  {
    // Si on se trouve dans la section "Tous les quizz"
    if(state.section === 0)
    {
      // On actualise la liste des quizz
      renderQuizzes();
    }

    // Si on se trouve dans la section "Mes quizz"
    else if(state.section === 1)
    {
      // On met à jour la liste des quizzes de l'utilisateur
      getUserQuizzes().then(function()
      {
        renderUserQuizzes();
        // On met à jour le quizz en cours de visualisation (si il y a)
        // sauf si l'utilsateur est en train de éditer/ajouter des éléments au 
        // quizz
        if(state.currentQuizz !== undefined && state.use === 0)
        {
          renderUserQuizz();
        }
      });
    }

    // Si on se trouve dans la section "Mes réponses"
    else if(state.section === 2)
    {
      // On met à jour la liste des quizzes répondus
      getUserAnswers().then(function()
      {
        renderUserAnswers();

        // On met à jour le quizz en cours visualisation (si il y a) 
        if(state.currentQuizz !== undefined)
        {
          renderUserAnswer();
        }
      });
    }
  }
}