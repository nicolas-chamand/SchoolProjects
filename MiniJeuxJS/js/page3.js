
$(function()
{
  // ------- Les variables et constantes ------- //
  var rayon = $('.draw')[0].offsetWidth/2;
  var i = 0;
  var animation;
  var y_n = 0;

  // ------- Les fonctions ------- //

  // function drawLine(p1, p2)
  // {
  //   let $div = $("<div class='line'><div>");
  
  //   let alpha= Math.atan((p2[1]-p1[1])/(p2[0]-p1[0]));
  //   let translate = [(p1[0]-rayon)*(Math.cos(alpha))+(rayon-p1[1])*(-Math.sin(alpha)), (p1[0]-rayon)*(Math.sin(alpha))+(rayon-p1[1])*(Math.cos(alpha))];
  //   $div.css('transform', `rotate(${-alpha}rad) translate(${translate[0]}px, ${translate[1]}px)`);
  //   $("#draw").append($div);
  // }

  function drawLine(p1, p2, y_n)
  {
    let $div = $("<div class='line'><div>");
    if(y_n)
    {
      $div.css('border', `1px solid rgb(${Math.floor(Math.random()*256)}, ${Math.floor(Math.random()*256)}, ${Math.floor(Math.random()*256)})`);
    }
    let alpha= Math.atan((p2[1]-p1[1])/(p2[0]-p1[0]));
    $div.css('transform', `translate(${p1[0]-rayon}px, ${rayon-p1[1]}px) rotate(${-alpha}rad) `);
    $(".draw").append($div);

  }

  function draw(n, modulo, y_n)
  {
    $('.draw').html('');
    let points = [[0,rayon]];
    for (let i=1; i<modulo; i++)
    {
      points.push([ rayon*Math.cos( (2*Math.PI/modulo)*i ), rayon*Math.sin( (2*Math.PI/modulo)*i ) ]);
    }
    for (let j=1; j<modulo; j++)
    {
      if(y_n)
      {
       drawLine(points[j], points[Math.floor((n*j)%modulo)], y_n); 
      }
      else
      {
        drawLine(points[j], points[Math.floor((n*j)%modulo)],); 
      }
    }
  }
  function animate()
  {
    animation = setInterval(function()
    {
      i+=0.1;
      draw(i, 300, y_n);
    }, 100);
  }
  function bindEvents()
  {
    $(window).resize(function()
    {
      rayon = $('.draw')[0].offsetWidth/2;
    });

    for(let i=2; i<8; i++)
    {
      $(`.tab_${i}`).click(function()
      {
        draw(i, 300, y_n);
      });
    }

    $(".animation").one('click', animate);

    $(".stop").click(function()
    {
      clearInterval(animation);
      $(".animation").one('click', animate);
    });

    $(".color").click(function()
    {
      y_n= (y_n+1)%2;
    });

    $('.clean').click(function()
    {
      i=0;
      $('.draw').html('');
    });

    $(".bts").click(function()
    {
      $(".draw").toggleClass('disp');
    });

  }

  // ------- Programme principale ------- //
	// Premier affichage de l'IA ------ //
	let tab_txt = ["Ceci est un projet réaliser uniquement avec du HTML, CSS et JavaScript ! :O ", "Le projet s'est inspiré des explications de Mickaël Launay. (aka Micmaths)", 
		"Voici le lien de sa vidéo explicatif si tu souhaites en savoir plus sur les tables de multiplications avant l'utilisation de cette page :",
    "<a href='https://www.youtube.com/watch?v=-X49VQgi86E'>Cliquez ici pour voir la vidéo !</a>"];
	let Elia = new IA('#help_text');
	setTimeout(function()
	{
		Elia.view(tab_txt);
		$('.fixed').toggleClass('toggle');
		$('#global').css('filter', 'blur(5px)');
		$('#arrow').css('transform', 'rotate(0deg)');
	}, 	500);
  
  bindEvents();
});