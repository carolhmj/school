Usando git e Github
===================
Aqui eu vou colocar uns links e tutoriais interessantes para se usar o github. 
Esse documento é escrito em [Github Flavored Markdown][md] e eu recomendo 
aprender como usar porque você pode usar no site todo. :grin:

Antes de tudo, é altamente recomendado que você rode esse comando para poder 
visualizar de forma decente as pastas com acentuação:
`git config --global core.quotepath false`

Workflow no git
---------------
Nesse projeto o nosso fluxo de trabalho vai ser baseado com esse [aqui][flow] 
lembrando que existe os [Issues e Milestones][issues] do projeto onde iremos 
colocar os deadlines, comentários e bug reporsts então comentem lá e prestem 
atenção no que é dito lá.

Eu achei dos tutorials de git, o que vem no [manual][man], um interativo do 
[GitHub][try], [the Simple guide][nobs], [GitHub Cheat Sheet][cheat], 
[Common Git Screwups][screw].

Também existe um [guia][guides] do próprio Github de como mexer no site.

Usando git no Windows
--------------------
Eu recomendo usar o [aplicativo do GitHub][githubwin] porque ele é muito fácil 
e não precisa nem ler o manual ou usar um tutorial, é fácil assim.

Instalando git no LEC
---------------------
Baixe o src do [git][git] e instale com os seguintes comandos
```Shell
make install NO_OPENSSL=1 NO_CURL=1
```
Logue e deslogue do computador e siga esse tutorial [aqui][ssh] :v:  
Agora é só usar os links do SSH que você acha na página do repositório.

[md]: https://help.github.com/articles/github-flavored-markdown/ "GitHub Flavored Markdown"
[flow]: https://guides.github.com/introduction/flow/ "Understanding the GitHub Flow"
[issues]: https://github.com/danisson/final-cg1/issues "Issues"
[man]: http://git-scm.com/docs/gittutorial "gittutorial(7)"
[try]: https://try.github.io/ "Try Git"
[nobs]: http://rogerdudler.github.io/git-guide/ "git - the simple guide"
[cheat]: http://snowdream86.gitbooks.io/github-cheat-sheet/content/en/index.html "GitHub Cheat Sheet"
[screw]: http://41j.com/blog/2015/02/common-git-screwupsquestions-solutions/ "Common Git Screwups and Questions"
[guides]: https://guides.github.com/ "Github Guides"
[githubwin]: https://windows.github.com/ "Github para Windows"
[git]: https://github.com/git/git/archive/master.zip
[ssh]: https://help.github.com/articles/generating-ssh-keys "Generating SSH keys"
