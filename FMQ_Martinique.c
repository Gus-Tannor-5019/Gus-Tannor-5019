// Addon-2016 Jason, французские миниквесты (ФМК) Мартиника
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Un bug évident. Parlez-en aux développeurs.";
			lien.l1 = " Oh, je vais.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестодатель
		case "carpenter":
			dialog.text = TimeGreeting()+", capitaine. Permettez-moi de me présenter - "+GetFullName(npchar)+". Bien que nous nous soyons déjà rencontrés il n'y a pas longtemps, je doute que vous vous souveniez de moi.";
            link.l1 = "Bonjour, monsieur. Et où pourrais-je vous voir avant?";
			link.l1.go = "carpenter_1";
		break;
		
		case "carpenter_1":
			sTemp = "lugger 'Adeline'";
			if (pchar.questTemp.Sharlie.Ship == "sloop") sTemp = "sloop 'Black Dog'";
			dialog.text = "Notre chantier naval. Vous avez acheté "+sTemp+". Tu t'en souviens? J'y suis menuisier.";
            link.l1 = "Ouais, j'ai vraiment acheté ce vaisseau. Alors que voulez-vous, monsieur "+GetFullName(npchar)+" ?";
            link.l1.go = "carpenter_2";
		break;
		
		case "carpenter_2":
			sld = characterFromId("FortFrance_shipyarder");
			dialog.text = "Notre constructeur de navires "+ GetFullName (sld) + " veut parler. Je crois qu'il a une sorte de proposition commerciale. Il a vu votre bateau dans notre port et m'a envoyé vous chercher. Accepteriez-vous gentiment l'invitation?";
			lien.l1 = " Très bien. Je rendrai visite à ton patron une fois que j'aurai fini mes affaires en ville.";
			link.l1.go = "carpenter_3";
		break;
		
		case "carpenter_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			pchar.questTemp.FMQM = "begin";
			AddQuestRecord("FMQ_Martinique", "1");
			SetFunctionTimerCondition("FMQM_Denial", 0, 0, 2, false);
		break;
		
		case "officer":
			PlaySound("VOICE\Russian\soldier_arest_4.wav");
			dialog.text = "Bien-bien... De nouveaux contrebandiers dans mon filet!";
			link.l1 = "Eh...";
			link.l1.go = "officer_1";
		break;
		
		case "officer_1":
			dialog.text = "Coupez la résine! Il y a plusieurs barils de résine à l'intérieur de ce chantier naval. Capitaine, vous les avez livrés à votre partenaire dans le crime. Vous êtes tous les deux en état d'arrestation et je confisque la cargaison au nom de la loi!";
			link.l1 = "...";
			link.l1.go = "officer_2";
		break;
		
		case "officer_2":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "officer_3":
			dialog.text = "Ne jouez pas au stupide, maître! Quels barils? Vous savez que je parle des barils que vous avez récemment déchargés du navire de ce marin! Vous pourrirez tous les deux dans les cachots! Bougez, connards...";
			link.l1 = "";
			link.l1.go = "officer_4";
		break;
		
		case "officer_4":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "officer_5":
			PlaySound("VOICE\Russian\soldier\soldier arest-02.wav");
			dialog.text = "Cette résine, mon cher maître constructeur naval, est un bien de valeur stratégique qui est sous le contrôle direct de notre gouverneur! Puisque vous prétendez que c'est tout à vous, faites - le à votre façon. Vous êtes en état d'arrestation, vous passerez cette nuit dans nos cachots confortables et demain vous nous ferez un rapport détaillé sur la façon dont vous les avez obtenus et dans quel but. Ne vous inquiétez pas, nous finirons par tout apprendre. Vous, capitaine, êtes libre de partir. C'est ton jour de chance.";
			link.l1 = "";
			link.l1.go = "officer_6";
		break;
		
		case "officer_6":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, characterFromID("FMQM_officer"));
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "FortFrance_town", "officers", "reload5_3", "FMQM_ArestContinue", 8);
		break;
		
		case "officer_7":
			PlaySound("VOICE\Russian\soldier_arest_2.wav");
			dialog.text = "Je savais qu'il y avait quelque chose qui n'allait pas avec ce vaisseau... On dirait que je vous ai sous-estimé, capitaine.";
			lien.l1 = " Exactement, lieutenant. Je ne suis pas si stupide. Votre joyeuse coopération avec le constructeur naval est compromise maintenant.";
			link.l1.go = "officer_8";
		break;
		
		case "officer_8":
			dialog.text = "Je comprends. Félicitations, vous devez être talentueux puisque vous avez réussi à me retrouver et à me surprendre. Maintenant, dis-moi ce que tu veux.";
			lien.l1 = " N'est-ce pas clair? J'ai besoin de récupérer ma résine. La résine que toi et ton pote m'avez volée.";
			link.l1.go = "officer_9";
		break;
		
		case "officer_9":
			dialog.text = "Bien. Vous pouvez l'avoir, mais seulement la moitié de votre lot. C'est tout ce que j'ai caché ici. J'espère que vous en trouverez assez, puisque c'est tout ce que je peux vous offrir.";
			lien.l1 = " Tu essaies toujours de me baiser? Indemnisez-moi l'autre moitié avec de l'or ou des biens cachés derrière vous.";
			link.l1.go = "officer_10";
		break;
		
		case "officer_10":
			dialog.text = "Pas une option. Adressez-vous à notre ami commun pour l'autre moitié.";
            link.l1 = "Vous vous moquez de moi ? Croyez-vous vraiment que "+GetFullName(characterFromId("FortFrance_shipyarder"))+" va me rendre mes barils ? C'est ridicule.";
            link.l1.go = "officer_11";
		break;
		
		case "officer_11":
			dialog.text = "Capitaine, prenez toute la résine que j'ai, prenez votre vie et foutez le camp d'ici. Je peux ajouter à ce marché ma promesse de ne pas vous causer d'ennuis à Saint-Pierre. C'est ma dernière offre.";
            lien.l1 = " Depuis quand ma vie fait-elle partie du marché? Ha!";
			link.l1.go = "officer_12";
		break;
		
		case "officer_12":
			dialog.text = "On dirait que tu te sens toujours invincible après le combat, capitaine. Laissez-moi vous expliquer ceci: c'étaient des recrues, non entraînées et non motivées, vous n'avez aucune chance contre mon équipe. Je pourrais te faire tuer ici sans marchandage, mais j'apprécie la vie de mes hommes. Quelqu'un d'entre eux pourrait être blessé ou même tué en train de vous tuer. Alors soit vous acceptez mon offre généreuse, soit vous restez ici pour toujours. Il est temps de choisir.";
			lien.l1 = " Allez vous faire foutre, lieutenant, mais je suis obligé d'accepter vos conditions. Je suis largement surpassé ici.";
			link.l1.go = "officer_13";
			link.l2 = "Trop confiant, lieutenant? Je suppose que je devrais vous donner une leçon, à vous et à vos mercenaires. Putain de chien en résine!";
			link.l2.go = "officer_15";
		break;
		
		case "officer_13":
			dialog.text = "Vous êtes un homme raisonnable, capitaine. Prenez vos barils et perdez-vous. Je devrais te prévenir, me pointer du doigt devant le gouverneur n'aidera pas. Je vais changer un emplacement de ma réserve aujourd'hui. Économisez votre temps.";
			lien.l1 = " N'allait pas. Je comprends la futilité de s'adresser aux autorités.";
			link.l1.go = "officer_14";
		break;
		
		case "officer_14":
			dialog.text = "Dépêche-toi, je n'ai pas beaucoup de temps à perdre.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQM_PeaceExit");
		break;
		
		case "officer_15":
			DialogExit();
			AddDialogExitQuestFunction("FMQM_BattleExit");
		break;
		
		case "greguar":
			dialog.text = "Oh! Quelle rencontre! Salut, monseigneur! Passer une bonne nuit?";
			lien.l1 = " Bonne nuit... ah, c'est toi! Je me souviens de toi, nous nous sommes rencontrés le tout premier jour de mon arrivée dans les Caraïbes. Monseigneur Grégoire Valinnie.";
			link.l1.go = "greguar_1";
		break;
		
		case "greguar_1":
			dialog.text = "Content que tu te souviennes encore. Je vois que tu es capitaine maintenant. Capitaine "+GetFullName(pchar)+". Félicitations.";
			lien.l1 = " Merci...";
			link.l1.go = "greguar_2";
		break;
		
		case "greguar_2":
			dialog.text = "Vous avez l'air troublé, capitaine. Que s'est-il passé ici? Quelque chose ne va pas?";
			lien.l1 = " Quelque chose ne va pas...";
			link.l1.go = "greguar_3";
		break;
		
		case "greguar_3":
			dialog.text = "Monsieur, plutôt que de rester au milieu de la rue, allons plutôt dans une taverne. Vous pourriez utiliser une pinte ou deux. On peut parler là-bas. Viens!";
			link.l1 = "...";
			link.l1.go = "greguar_4";
		break;
		
		case "greguar_4":
			DialogExit();
			NextDiag.CurrentNode = "greguar_5"; 
			FreeSitLocator("Fortfrance_tavern", "sit_front4");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Fortfrance_tavern", "sit", "sit_front4", "FMQM_InTavern", -1);
		break;
		
		case "greguar_5":
			LAi_SetSitType(Pchar);
			dialog.text = "Versez - le, capitaine...";
			lien.l1 = " Allez-y..";
			link.l1.go = "greguar_6";
		break;
		
		case "greguar_6":
			LAi_Fade("", "");
			WaitDate("",0,0,0,1,20);
			RecalculateJumpTable();
			dialog.text = "Wow... Maintenant, s'il te plaît, dis-moi ce qui ne va pas? Tu ressembles à ce gars qu'ils ont pendu la semaine dernière. Il avait exactement le même visage lorsqu'il se tenait sur la potence.";
			lien.l1 = " Voyez, monsieur Grégoire... Disons simplement que j'ai des problèmes au travail.";
			link.l1.go = "greguar_7";
		break;
		
		case "greguar_7":
			dialog.text = "Capitaine, vous pouvez tout partager avec moi. Je ne vais pas vous vendre au gouverneur ou au commandant, vous pouvez me faire confiance là-dessus. Tu ne me fais pas confiance?";
			lien.l1 = " Je te fais confiance, monseigneur.";
			link.l1.go = "greguar_8";
		break;
		
		case "greguar_8":
			dialog.text = "Puis confessez et mettez un peu d'aisance dans votre âme. Je pourrais être en mesure de vous aider.";
			lien.l1 = " Un constructeur de navires local m'a engagé pour piller une caravane espagnole de Port-au-Espagne. Il avait un fort besoin en résine, c'était mon objectif et il a promis de payer quinze doublons par baril. J'ai retrouvé la caravane, je l'ai pillée et j'ai amené les marchandises ici. Ils avaient réparé mon navire et déchargé les barils au chantier naval. Nous étions sur le point de conclure notre marché lorsque cet officier s'est présenté... Je me demande comment il a pu le savoir?";
			link.l1.go = "greguar_9";
		break;
		
		case "greguar_9":
			dialog.text = "";
			link.l1 = "C'était ça, ils nous avaient. Je pense que je devrais donner un crédit au constructeur naval - il s'est jeté tout le blâme sur lui-même, leur a dit que la résine était sa propriété et que je n'avais rien à voir avec cela. À la fin, il est arrêté et ma pièce est partie. Le désordre avec la caravane espagnole était une perte de temps et d'argent, même si j'ai eu la chance de ne pas finir en prison. Versez-le encore, monsieur Grégoire.";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_10":
			dialog.text = "Donc, le constructeur de navires est en état d'arrestation?";
			lien.l1 = " Eh bien, oui. Il a été emmené en prison par l'officier dont je parlais. Tu aurais dû les voir.";link.l1.go = "greguar_11";
		break;
		
		case "greguar_11":
			dialog.text = "Oui, je les ai vus tous les deux, même si je n'avais aucune idée que le lieutenant Félicien Gronier pourrait éventuellement arrêter son vieil ami.";
			lien.l1 = " CE... qu'est-ce que tu viens de dire?";
			link.l1.go = "greguar_12";
		break;
		
		case "greguar_12":
			dialog.text = "Vous avez bien entendu. Le lieutenant Félicien Gronier et le constructeur naval "+GetFullName(characterFromId("Fort France_shipyard"))+ " sont de vieux amis. Ils servaient ensemble dans l'armée en Europe. Frontier est resté dans l'armée et "+GetFullName(characterFromId("Fort France_shipyard"))+" a réussi à démarrer sa propre entreprise.";
			lien.l1 = " Donc ils se connaissent... Maintenant je vois...";
			link.l1.go = "greguar_13";
		break;
		
		case "greguar_13":
			dialog.text = "Ma chère " +pchar.name+", on dirait que tu t'es fait avoir. Vous êtes encore un nouveau venu ici et ils l'avaient utilisé. Je parie cent doublons que monsieur " + GetFullName (characterFromId ("Fort France_shipyard"))+ " fera à nouveau le tour de son chantier naval dans trois jours ou moins.";
			lien.l1 = " Il semble que vous ayez raison, monsieur. Ils m'ont baisé. Impossible que cet officier puisse savoir pour la résine. Timing parfait aussi.";
			link.l1.go = "greguar_14";
		break;
		
		case "greguar_14":
			dialog.text = "C'est les Caraïbes, monseigneur"+pchar.name+". Habituez-vous à ça. Oubliez les regards, la pire racaille ici ressemble toujours à un noble honoré.";
			lien.l1 = " J'ai déjà entendu cette phrase quelque part auparavant... Que dois-je en faire? Dois-je m'adresser au gouverneur?";
			link.l1.go = "greguar_15";
		break;
		
		case "greguar_15":
			dialog.text = "Je crains que dans ce cas " + GetFullName (characterFromId ("Fort France_shipyard"))+ " leur raconte une autre histoire et que vous finissiez en prison.";
			lien.l1 = " Chiffres. Très bien alors! Puisque la loi n'est pas de mon côté, je vais le faire à ma façon bon sang! Je ne vais pas abandonner comme ça.";
			link.l1.go = "greguar_16";
		break;
		
		case "greguar_16":
			dialog.text = "S'il te plaît calme-toi " +pchar.name+". C'est la colère et le rhum qui parlent, pas toi. Dormez et réfléchissez-y à nouveau. Peut-être que ce serait mieux pour toi de laisser tomber. Le lieutenant Félicien Gronier et " + GetFullName (characterFromId ("Fort France_shipyard")) + " sont des gens puissants ici, ils sont bien au-dessus de votre ligue. Ne fais rien de stupide.";
			lien.l1 = " On verra. Merci de m'éclairer. C'est bien que je t'ai rencontré.";
			link.l1.go = "greguar_17";
		break;
		
		case "greguar_17":
			dialog.text = "Sois prudent. Garde à l'esprit ce que je t'ai dit.";
			lien.l1 = " Je le ferai. Maintenant, prenons un dernier verre!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQM_OutTavern");
		break;
		
		case "greguar_18":
			dialog.text = "Captain "+GetFullName(pchar)+"!";
			link.l1 = "Oh, monsieur Grégoire! Encore toi!";
			link.l1.go = "greguar_19";
		break;
		
		case "greguar_19":
			dialog.text = "Oui. Après notre conversation de taverne, je me suis renseigné sur le lieutenant Félicien Gronier. Il s'avère qu'il a demandé un congé de dix jours il n'y a pas longtemps. Sa pétition a été approuvée. Je l'ai vu aujourd'hui, il a pris une chaloupe pour une tartane qui a rapidement navigué vers la Guadeloupe. Elle s'appelle la Topaze\Je ne t'ai pas tout dit, c'est à toi de l'appeler maintenant. Je suis sûr que vous pouvez voir le schéma dans l'appel soudain de Gronier à prendre congé et à s'éloigner de l'île sur une tartane fraîchement construite.";
			lien.l1 = " Bon sang, c'est du cristal pour moi maintenant, c'est sûr! Ce tartane a ma résine stockée dans une soute! Monsieur Grégoire merci, vous êtes vraiment passé au travers! Y a-t-il quelque chose que je pourrais faire pour toi en retour?";
			link.l1.go = "greguar_20";
		break;
		
		case "greguar_20":
			dialog.text = "Oh, allez mon ami. Nous sommes des nobles, nous devrions nous entraider. C'est ainsi que nous vivons. Je crois que tu aurais fait la même chose si j'avais été à ta place. Ne perdez pas une minute, naviguez vers le nord et trouvez l'officier. Ne vous engagez pas dans le combat, traquez-le simplement et découvrez ce qu'il fait. Dépêchez-vous, capitaine!";
			lien.l1 = " Merci encore!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQM_HurryToSea");
		break;
		
		case "pirate":
			dialog.text = "Qu'est-ce que tu regardes? Que veux-tu ici?";
			lien.l1 = "Hey mon pote, je suis après mes goodies. Tu vois ces barils là-bas? C'est ma résine pour laquelle ils ne m'ont pas payé un centime.";
			link.l1.go = "pirate_1";
		break;
		
		case "pirate_1":
			dialog.text = "T'es un idiot ou quoi? Perdez-vous pendant que vous le pouvez encore!";
			lien.l1 = " J'ai fait trop d'efforts pour obtenir cette résine pour permettre à quelques immondes racailles de m'arrêter.";
			link.l1.go = "pirate_2";
		break;
		
		case "pirate_2":
			dialog.text = "Nous allons enterrer votre costume de fantaisie ici!";
			lien.l1 = " Le nombre de salauds est sur le point de diminuer aujourd'hui!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQM_ShoreFight");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
