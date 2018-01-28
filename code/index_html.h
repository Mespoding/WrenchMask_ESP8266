const char* index_html = R"(
<html>
    <head>
        <meta http-equiv="Content-Type" name="viewport" content="width=device-width, initial-scale=1">
        <link href="//netdna.bootstrapcdn.com/bootstrap/3.1.1/css/bootstrap.min.css" rel="stylesheet" type="text/css">
        <title>
            Wrench Expression
        </title>
        <style type="text/css">
body {
            background-color: #A9E2F3;
            padding-top: 45px;
            padding-bottom: 40px;
            
        }
        .col-center-block {  
        float: none;  
        display: block;  
        margin-left: auto;  
        margin-right: auto;  
        }  
        </style>
    </head>
    <body>
        <div class="container">
            <div class="jumbotron">
                <h2>
                    通过选择面具表情或者自定义显示的符号
                </h2><br>
                <form action="/exp" method="post">
                    <div class="form-group">
                        <div class="row">
                            <label for="inputEmail3" class="col-xs-1 control-label">显示</label>
                            <div class="col-xs-10">
                                <input class="form-control input-lg" type="text" id="message" name="message" placeholder="输入要自定义显示内容">
                            </div>
                        </div><br>
                        <div class="row">
                            <label for="inputEmail3" class="col-xs-1 control-label">表情</label>
                            <div class="col-xs-10">
                                <select class="form-control input-lg" name="exp">
                                    <option value="255">
                                        ....
                                    </option>
                                    <option value="0">
                                        \ /
                                    </option>
                                    <option value="1">
                                        / \
                                    </option>
                                    <option value="2">
                                        = =
                                    </option>
                                    <option value="3">
                                        ^ ^
                                    </option>
                                    <option value="4">
                                        &gt; &lt;&lt;/option&gt;
                                    </option>
                                    <option value="5">
                                        # #
                                    </option>
                                    <option value="6">
                                        x x
                                    </option>
                                    <option value="7">
                                        ❤ ❤
                                    </option>
                                    <option value="8">
                                        ? ?
                                    </option>
                                    <option value="9">
                                        口 口
                                    </option>
                                    <option value="10">
                                        0 0
                                    </option>
                                    <option value="11">
                                        1 1
                                    </option>
                                    <option value="12">
                                        2 2
                                    </option>
                                </select>
                            </div>
                        </div><br>
                        <div class="row">
                            <label for="inputEmail3" class="col-xs-1 control-label">亮度</label>
                            <div class="col-xs-10">
                                <select class="form-control input-lg" name="ligthness">
                                    <option value="255">
                                        ....
                                    </option>
                                    <option value="0">
                                        0
                                    </option>
                                    <option value="1">
                                        1
                                    </option>
                                    <option value="2">
                                        2
                                    </option>
                                    <option value="3">
                                        3
                                    </option>
                                    <option value="4">
                                        4
                                    </option>
                                    <option value="5">
                                        5
                                    </option>
                                    <option value="6">
                                        6
                                    </option>
                                    <option value="7">
                                        7
                                    </option>
                                    <option value="8">
                                        8
                                    </option>
                                    <option value="9">
                                        9
                                    </option>
                                    <option value="10">
                                        10
                                    </option>
                                    <option value="11">
                                        11
                                    </option>
                                    <option value="12">
                                        12
                                    </option>
                                    <option value="13">
                                        13
                                    </option>
                                    <option value="14">
                                        14
                                    </option>
                                    <option value="15">
                                        15
                                    </option>
                                </select>
                            </div>
                        </div><label class="checkbox-inline"><input type="radio" id="inlineRadio1" value="1" name="EXPRadio"> 间闪</label> <label class="checkbox-inline"><input type="radio" id="inlineRadio1" value="2" name="EXPRadio"> 随机</label> <label class="checkbox-inline"><input type="radio" id="inlineRadio1" value="3" name="EXPRadio"> 不闪</label><br>
                    </div><button type="submit" class="btn btn-info btn-lg vertical-center">(。・`ω´・) blinblinblin</button>
                </form>
            </div>
        </div>
    </body>
</html>
)";
