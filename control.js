flag = 0;
var div = document.querySelector('div');
var section = document.querySelector('section');


var apiname;
var apiline;
var apis;
var requestURL;
var request;
request = new XMLHttpRequest();

function clearcontent(elementID) {
    var div = document.getElementById(elementID);
    while (div.firstChild) {
        div.removeChild(div.firstChild);
    }
}

function clearcache(elementID) {
    var section = document.getElementById(elementID);
    while (section.firstChild) {
        section.removeChild(section.firstChild);
    }
}

function result() {
    var answer = request.response;
    var data = answer["data"];
    var Article = document.createElement('article');
    var PC = document.createElement('p');
    var rax = document.createElement('p');
    var rcx = document.createElement('p');
    var rdx = document.createElement('p');
    var rbx = document.createElement('p');
    var rsp = document.createElement('p');
    var rbp = document.createElement('p');
    var rsi = document.createElement('p');
    var rdi = document.createElement('p');
    var r8 = document.createElement('p');
    var r9 = document.createElement('p');
    var r10 = document.createElement('p');
    var r11 = document.createElement('p');
    var r12 = document.createElement('p');
    var r13 = document.createElement('p');
    var r14 = document.createElement('p');
    var memlable = document.createElement('p');
    var Memory = document.createElement('p');
    var ZF = document.createElement('p');
    var SF = document.createElement('p');
    var OF = document.createElement('p');
    var STAT = document.createElement('p');

    PC.textContent = 'PC: ' + data[flag].PC;
    PC.id = 'pc';
    rax.textContent = 'rax: ' + data[flag].REG.rax;
    rcx.textContent = 'rcx: ' + data[flag].REG.rcx;
    rdx.textContent = 'rdx: ' + data[flag].REG.rdx;
    rbx.textContent = 'rbx: ' + data[flag].REG.rbx;
    rsp.textContent = 'rsp: ' + data[flag].REG.rsp;
    rbp.textContent = 'rbp: ' + data[flag].REG.rbp;
    rsi.textContent = 'rsi: ' + data[flag].REG.rsi;
    rdi.textContent = 'rdi: ' + data[flag].REG.rdi;
    r8.textContent = 'r8: ' + data[flag].REG.r8;
    r9.textContent = 'r9: ' + data[flag].REG.r9;
    r10.textContent = 'r10: ' + data[flag].REG.r10;
    r11.textContent = 'r11: ' + data[flag].REG.r11;
    r12.textContent = 'r12: ' + data[flag].REG.r12;
    r13.textContent = 'r13: ' + data[flag].REG.r13;
    r14.textContent = 'r14: ' + data[flag].REG.r14;

    memlable.textContent = 'MEMORY:';
    memlable.id = 'mem';

    for (i in data[flag].MEM) {
        var val = i;
        var s = data[flag].MEM[val.toString()];
        if (s != undefined) {
            Memory.textContent += i + ': ' + s + ' \n ';
        }
        i += 8;
    }

    ZF.textContent = 'ZF: ' + data[flag].CC.ZF;
    ZF.id = 'cc';
    SF.textContent = 'SF: ' + data[flag].CC.SF;
    SF.id = 'cc';
    OF.textContent = 'OF: ' + data[flag].CC.OF;
    OF.id = 'cc';
    STAT.textContent = 'STAT: ' + data[flag].STAT;
    STAT.id = 'cc';


    Article.appendChild(PC);
    Article.appendChild(rax);
    Article.appendChild(rcx);
    Article.appendChild(rdx);
    Article.appendChild(rbx);
    Article.appendChild(rsp);
    Article.appendChild(rbp);
    Article.appendChild(rsi);
    Article.appendChild(rdi);
    Article.appendChild(r8);
    Article.appendChild(r9);
    Article.appendChild(r10);
    Article.appendChild(r11);
    Article.appendChild(r12);
    Article.appendChild(r13);
    Article.appendChild(r14);
    Article.appendChild(memlable);
    Article.appendChild(Memory);
    Article.appendChild(ZF);
    Article.appendChild(SF);
    Article.appendChild(OF);
    Article.appendChild(STAT);

    div.appendChild(Article);

    if (flag == data.length - 1) flag = 0;
    else flag++;
}

function cache(){
    var answer = request.response;
    var data = answer["data"];
    var c = data[flag].cache;
    var Article = document.createElement('article');
    
    var cache = document.createElement('p');
    var cache0 = document.createElement('p');
    var cache1 = document.createElement('p');
    var cache2 = document.createElement('p');
    var cache3 = document.createElement('p');
    var cache4 = document.createElement('p');
    var cache5 = document.createElement('p');
    var cache6 = document.createElement('p');
    var cache7 = document.createElement('p');
    var cache8 = document.createElement('p');
    var cache9 = document.createElement('p');
    var cache10 = document.createElement('p');
    var cache11 = document.createElement('p');
    var cache12 = document.createElement('p');
    var cache13 = document.createElement('p');
    var cache14 = document.createElement('p');
    var cache15 = document.createElement('p');
    
    cache.textContent = 'CACHE:';
    cache.id = 'c';
    cache0.textContent = c['0'][0].valid + " | " + c['0'][1].tag + " | " + c['0'][2].block[0] + " " + c['0'][2].block[1] + " " + c['0'][2].block[2] + " " + c['0'][2].block[3] + " " + c['0'][2].block[4] + " " + c['0'][2].block[5] + " " + c['0'][2].block[6] + " " + c['0'][2].block[7] + " " + c['0'][2].block[8] + " " + c['0'][2].block[9] + " " + c['0'][2].block[10] + " " + c['0'][2].block[11] + " " + c['0'][2].block[12] + " " + c['0'][2].block[13] + " " + c['0'][2].block[14] + " " + c['0'][2].block[15];
    cache1.textContent = c['1'][0].valid + " | " + c['1'][1].tag + " | " + c['1'][2].block[0] + " " + c['1'][2].block[1] + " " + c['1'][2].block[2] + " " + c['1'][2].block[3] + " " + c['1'][2].block[4] + " " + c['1'][2].block[5] + " " + c['1'][2].block[6] + " " + c['1'][2].block[7] + " " + c['1'][2].block[8] + " " + c['1'][2].block[9] + " " + c['1'][2].block[10] + " " + c['1'][2].block[11] + " " + c['1'][2].block[12] + " " + c['1'][2].block[13] + " " + c['1'][2].block[14] + " " + c['1'][2].block[15];
    cache2.textContent = c['2'][0].valid + " | " + c['2'][1].tag + " | " + c['2'][2].block[0] + " " + c['2'][2].block[1] + " " + c['2'][2].block[2] + " " + c['2'][2].block[3] + " " + c['2'][2].block[4] + " " + c['2'][2].block[5] + " " + c['2'][2].block[6] + " " + c['2'][2].block[7] + " " + c['2'][2].block[8] + " " + c['2'][2].block[9] + " " + c['2'][2].block[10] + " " + c['2'][2].block[11] + " " + c['2'][2].block[12] + " " + c['2'][2].block[13] + " " + c['2'][2].block[14] + " " + c['2'][2].block[15];
    cache3.textContent = c['3'][0].valid + " | " + c['3'][1].tag + " | " + c['3'][2].block[0] + " " + c['3'][2].block[1] + " " + c['3'][2].block[2] + " " + c['3'][2].block[3] + " " + c['3'][2].block[4] + " " + c['3'][2].block[5] + " " + c['3'][2].block[6] + " " + c['3'][2].block[7] + " " + c['3'][2].block[8] + " " + c['3'][2].block[9] + " " + c['3'][2].block[10] + " " + c['3'][2].block[11] + " " + c['3'][2].block[12] + " " + c['3'][2].block[13] + " " + c['3'][2].block[14] + " " + c['3'][2].block[15];
    cache4.textContent = c['4'][0].valid + " | " + c['4'][1].tag + " | " + c['4'][2].block[0] + " " + c['4'][2].block[1] + " " + c['4'][2].block[2] + " " + c['4'][2].block[3] + " " + c['4'][2].block[4] + " " + c['4'][2].block[5] + " " + c['4'][2].block[6] + " " + c['4'][2].block[7] + " " + c['4'][2].block[8] + " " + c['4'][2].block[9] + " " + c['4'][2].block[10] + " " + c['4'][2].block[11] + " " + c['4'][2].block[12] + " " + c['4'][2].block[13] + " " + c['4'][2].block[14] + " " + c['4'][2].block[15];
    cache5.textContent = c['5'][0].valid + " | " + c['5'][1].tag + " | " + c['5'][2].block[0] + " " + c['5'][2].block[1] + " " + c['5'][2].block[2] + " " + c['5'][2].block[3] + " " + c['5'][2].block[4] + " " + c['5'][2].block[5] + " " + c['5'][2].block[6] + " " + c['5'][2].block[7] + " " + c['5'][2].block[8] + " " + c['5'][2].block[9] + " " + c['5'][2].block[10] + " " + c['5'][2].block[11] + " " + c['5'][2].block[12] + " " + c['5'][2].block[13] + " " + c['5'][2].block[14] + " " + c['5'][2].block[15];
    cache6.textContent = c['6'][0].valid + " | " + c['6'][1].tag + " | " + c['6'][2].block[0] + " " + c['6'][2].block[1] + " " + c['6'][2].block[2] + " " + c['6'][2].block[3] + " " + c['6'][2].block[4] + " " + c['6'][2].block[5] + " " + c['6'][2].block[6] + " " + c['6'][2].block[7] + " " + c['6'][2].block[8] + " " + c['6'][2].block[9] + " " + c['6'][2].block[10] + " " + c['6'][2].block[11] + " " + c['6'][2].block[12] + " " + c['6'][2].block[13] + " " + c['6'][2].block[14] + " " + c['6'][2].block[15];
    cache7.textContent = c['7'][0].valid + " | " + c['7'][1].tag + " | " + c['7'][2].block[0] + " " + c['7'][2].block[1] + " " + c['7'][2].block[2] + " " + c['7'][2].block[3] + " " + c['7'][2].block[4] + " " + c['7'][2].block[5] + " " + c['7'][2].block[6] + " " + c['7'][2].block[7] + " " + c['7'][2].block[8] + " " + c['7'][2].block[9] + " " + c['7'][2].block[10] + " " + c['7'][2].block[11] + " " + c['7'][2].block[12] + " " + c['7'][2].block[13] + " " + c['7'][2].block[14] + " " + c['7'][2].block[15];
    cache8.textContent = c['8'][0].valid + " | " + c['8'][1].tag + " | " + c['8'][2].block[0] + " " + c['8'][2].block[1] + " " + c['8'][2].block[2] + " " + c['8'][2].block[3] + " " + c['8'][2].block[4] + " " + c['8'][2].block[5] + " " + c['8'][2].block[6] + " " + c['8'][2].block[7] + " " + c['8'][2].block[8] + " " + c['8'][2].block[9] + " " + c['8'][2].block[10] + " " + c['8'][2].block[11] + " " + c['8'][2].block[12] + " " + c['8'][2].block[13] + " " + c['8'][2].block[14] + " " + c['8'][2].block[15];
    cache9.textContent = c['9'][0].valid + " | " + c['9'][1].tag + " | " + c['9'][2].block[0] + " " + c['9'][2].block[1] + " " + c['9'][2].block[2] + " " + c['9'][2].block[3] + " " + c['9'][2].block[4] + " " + c['9'][2].block[5] + " " + c['9'][2].block[6] + " " + c['9'][2].block[7] + " " + c['9'][2].block[8] + " " + c['9'][2].block[9] + " " + c['9'][2].block[10] + " " + c['9'][2].block[11] + " " + c['9'][2].block[12] + " " + c['9'][2].block[13] + " " + c['9'][2].block[14] + " " + c['9'][2].block[15];
    cache10.textContent = c['10'][0].valid + " | " + c['10'][1].tag + " | " + c['10'][2].block[0] + " " + c['10'][2].block[1] + " " + c['10'][2].block[2] + " " + c['10'][2].block[3] + " " + c['10'][2].block[4] + " " + c['10'][2].block[5] + " " + c['10'][2].block[6] + " " + c['10'][2].block[7] + " " + c['10'][2].block[8] + " " + c['10'][2].block[9] + " " + c['10'][2].block[10] + " " + c['10'][2].block[11] + " " + c['10'][2].block[12] + " " + c['10'][2].block[13] + " " + c['10'][2].block[14] + " " + c['10'][2].block[15];
    cache11.textContent = c['11'][0].valid + " | " + c['11'][1].tag + " | " + c['11'][2].block[0] + " " + c['11'][2].block[1] + " " + c['11'][2].block[2] + " " + c['11'][2].block[3] + " " + c['11'][2].block[4] + " " + c['11'][2].block[5] + " " + c['11'][2].block[6] + " " + c['11'][2].block[7] + " " + c['11'][2].block[8] + " " + c['11'][2].block[9] + " " + c['11'][2].block[10] + " " + c['11'][2].block[11] + " " + c['11'][2].block[12] + " " + c['11'][2].block[13] + " " + c['11'][2].block[14] + " " + c['11'][2].block[15];
    cache12.textContent = c['12'][0].valid + " | " + c['12'][1].tag + " | " + c['12'][2].block[0] + " " + c['12'][2].block[1] + " " + c['12'][2].block[2] + " " + c['12'][2].block[3] + " " + c['12'][2].block[4] + " " + c['12'][2].block[5] + " " + c['12'][2].block[6] + " " + c['12'][2].block[7] + " " + c['12'][2].block[8] + " " + c['12'][2].block[9] + " " + c['12'][2].block[10] + " " + c['12'][2].block[11] + " " + c['12'][2].block[12] + " " + c['12'][2].block[13] + " " + c['12'][2].block[14] + " " + c['12'][2].block[15];
    cache13.textContent = c['13'][0].valid + " | " + c['13'][1].tag + " | " + c['13'][2].block[0] + " " + c['13'][2].block[1] + " " + c['13'][2].block[2] + " " + c['13'][2].block[3] + " " + c['13'][2].block[4] + " " + c['13'][2].block[5] + " " + c['13'][2].block[6] + " " + c['13'][2].block[7] + " " + c['13'][2].block[8] + " " + c['13'][2].block[9] + " " + c['13'][2].block[10] + " " + c['13'][2].block[11] + " " + c['13'][2].block[12] + " " + c['13'][2].block[13] + " " + c['13'][2].block[14] + " " + c['13'][2].block[15];
    cache14.textContent = c['14'][0].valid + " | " + c['14'][1].tag + " | " + c['14'][2].block[0] + " " + c['14'][2].block[1] + " " + c['14'][2].block[2] + " " + c['14'][2].block[3] + " " + c['14'][2].block[4] + " " + c['14'][2].block[5] + " " + c['14'][2].block[6] + " " + c['14'][2].block[7] + " " + c['14'][2].block[8] + " " + c['14'][2].block[9] + " " + c['14'][2].block[10] + " " + c['14'][2].block[11] + " " + c['14'][2].block[12] + " " + c['14'][2].block[13] + " " + c['14'][2].block[14] + " " + c['14'][2].block[15];
    cache15.textContent = c['15'][0].valid + " | " + c['15'][1].tag + " | " + c['15'][2].block[0] + " " + c['15'][2].block[1] + " " + c['15'][2].block[2] + " " + c['15'][2].block[3] + " " + c['15'][2].block[4] + " " + c['15'][2].block[5] + " " + c['15'][2].block[6] + " " + c['15'][2].block[7] + " " + c['15'][2].block[8] + " " + c['15'][2].block[9] + " " + c['15'][2].block[10] + " " + c['15'][2].block[11] + " " + c['15'][2].block[12] + " " + c['15'][2].block[13] + " " + c['15'][2].block[14] + " " + c['15'][2].block[15];

    Article.appendChild(cache);
    Article.appendChild(cache0);
    Article.appendChild(cache1);
    Article.appendChild(cache2);
    Article.appendChild(cache3);
    Article.appendChild(cache4);
    Article.appendChild(cache5);
    Article.appendChild(cache6);
    Article.appendChild(cache7);
    Article.appendChild(cache8);
    Article.appendChild(cache9);
    Article.appendChild(cache10);
    Article.appendChild(cache11);
    Article.appendChild(cache12);
    Article.appendChild(cache13);
    Article.appendChild(cache14);
    Article.appendChild(cache15);

    section.appendChild(Article);

    if (flag == data.length - 1) flag = 0;
    else flag++;
}

window.addEventListener('load', () => {
    const f = document.getElementById('file');
    f.addEventListener('change', evt => {
        let input = evt.target;
        if (input.files.length == 0) {
            console.log('No file selected');
            return;
        }
        const file = input.files[0];
        const reader = new FileReader();
        reader.onload = () => {
            const pre = document.getElementById('pre1');
            pre.innerHTML = reader.result;
        };

        reader.readAsText(file);
        apiname = document.getElementById('file').value;
        apiline = apiname.split('.');
        apis = 'http://localhost:8000//' + apiline[0].substr(12, 30) + '.json';
        requestURL = apis;
        request.open('GET', requestURL);
        request.responseType = 'json';
        request.send();
        request.onload = function () { }
    });
});
// https://www.jb51.net/article/253234.htm

var TRange = null
function findString() {
    var answer = request.response;
    var data = answer["data"];
    var pc = data[flag].PC;
    str = pc.toString(16) + ':';
    if (str.length == 2) str = '0x00' + str;
    else if (str.length == 3) str = '0x0' + str;
    else if (str.length == 4) str = '0x' + str;

    var txt = document.getElementById('pre1').innerHTML;
    var lines = txt.split('\n');
    for (var i = 0; i < lines.length; i++) {
        if (str == lines[i].slice(0, 6)) {
            str = lines[i];
            break;
        }
    }

    var strFound;
    strFound = self.find(str);

    if (window.find) {
        // CODE FOR BROWSERS THAT SUPPORT window.find

        if (strFound && self.getSelection && !self.getSelection().anchorNode) {

            strFound = self.find(str)
        }
        if (!strFound) {
            strFound = self.find(str, 0, 1)
            while (self.find(str, 0, 1)) continue
        }
    }
    else if (navigator.appName.indexOf("Microsoft") != -1) {
        // EXPLORER-SPECIFIC CODE
        if (TRange != null) {
            TRange.collapse(false)
            strFound = TRange.findText(str)
            if (strFound) TRange.select()
        }
        if (TRange == null || strFound == 0) {
            TRange = self.document.body.createTextRange()
            strFound = TRange.findText(str)
            if (strFound) TRange.select()
        }
    }
    else if (navigator.appName == "Opera") {
        alert("Opera browsers not supported, sorry...")
        return;
    }

    if (!strFound) alert("String '" + str + "' not found!")
    return;
}
// https://blog.csdn.net/weixin_42571979/article/details/120067632

