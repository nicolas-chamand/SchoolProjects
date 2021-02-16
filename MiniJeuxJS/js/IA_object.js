

// -------- Objet IA -------- //
function IA(id_div)
{	
	this.id_div = id_div;
}

IA.prototype.create_p = function(strings)
{
	let paras = [];
	$(strings).each(function(i, elt)
	{
		paras.push($(`<p class='hidden'><span class="msg">${elt}</span></p>`));
	});
	return paras;
}

IA.prototype.view = function(strings)
{
	let self = this;
	$(this.create_p(strings)).each(function(i, elt)
	{
		$(self.id_div).append(elt.delay(i*2000).fadeIn(1500));
	});
}

// IA.prototype.qcm = function(QnA, answers)
// {
// 	let QnAs=[QnA[0]];
// 	for (i of answers)
// 	{
// 		QnAs.push(i);
// 	}
// 	let $qcm = new IA(QnAs, '#global');

// 	let tab_qcm = $qcm.create_p('txt').slice(1,tab_qcm.length);
// 	tab_qcm.forEach(function(elt)
// 	{
// 		$(elt).click(function()
// 		{
// 			if ($(elt).text() != QnA[1])
// 			{
// 				$(elt).css('background-color', 'red');
// 			}
// 			else
// 			{
// 				$(elt).css('background-color', 'green');
// 			}
// 		});
// 	});
// 	$qcm.view(tab_qcm);
// }

function IAEvents()
	{
		// ------ Les events de l'affichage IA ------ // 
		$('#toggle_help').click(function()
		{
			$('.fixed').toggleClass('toggle');
			if($('.fixed').hasClass('toggle'))
			{
				$('#arrow').css('transform', 'rotate(180deg)');
				$('#global').css('filter', 'blur(0px)');
			}
			else
			{
				$('#arrow').css('transform', 'rotate(0deg)');
				$('#global').css('filter', 'blur(5px)');
			}
		});

		$('#toggle_help').hover(function()
		{
			$('#arrow').attr('src', '../images/left-arrow-red.png');
		}, function()
		{
			$('#arrow').attr('src', '../images/left-arrow.png');
		});	
	}
IAEvents();
