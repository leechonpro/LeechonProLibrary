use crate::FileIO;
use std::collections::HashMap;

pub enum JsonType{
    Null( u8 ),
    Integer(i32),
    Float(f32),
    Text(String),
    Bool(bool),
    Object( HashMap<String, JsonType> ),
    Array( Vec<JsonType> )
}

pub struct JsonParser
{
    file: FileIO,
}

impl JsonParser
{
    pub fn new( file_name: &str ) -> Self
    {
        JsonParser
        {
            file: FileIO::new( &file_name )
        }
    }

    pub fn create_json( &mut self )
    {
        let _ = self.file.write_to_new_file("{{}}");
    }
    
    pub fn is_exist( &mut self ) -> bool
    {
        self.file.is_exist()
    }

    fn p_get_next_data( &mut self )->(String,JsonType)
    {
        if self.is_exist()
        {
            let key = self.p_get_next_key();
            let val = self.p_get_next_value();
            ( key, val )
        }
        else
        {
            ( String::new(), JsonType::Null(0) )
        }
    }

    fn p_get_next_key( &mut self ) -> String
    {
        if self.is_exist()
        {
            let _ = self.file.read_till_delimeters("\"".to_string() );
            let key = self.file.read_till_delimeters("\"".to_string());
            _ = self.file.read_till_delimeters(":".to_string() );
            key            
        }
        else
        {
            String::new()
        }
    }

    fn p_get_next_value( &mut self ) -> JsonType
    {
        let result: JsonType;
        if self.is_exist()
        {
            let origin = self.file.read_till_delimeters( String::from( ",][}{" ) );
            let text = origin.trim();
            let mut last_char = self.file.get_last_char();
            if '{' == last_char
            {
                let mut obj: HashMap<String,JsonType> = HashMap::new();

                while '}' != last_char
                {
                    let (key,val) = self.p_get_next_data();
                    if false == key.is_empty()
                    {
                        obj.insert( key,val );
                        last_char = self.file.get_last_char();
                    }
                    else
                    {
                        break;
                    }
                }

                result = JsonType::Object( obj );
            }
            else if '[' == last_char 
            {
                let mut arr: Vec<JsonType> = Vec::new();

                while ']' != last_char
                {
                    let val = self.p_get_next_value();
                    last_char = self.file.get_last_char();
                    
                    match val
                    {
                        JsonType::Null(_) => continue,
                        _=> arr.push(val),
                    }
                }


                result = JsonType::Array( arr );
            }
            else
            {
                if ( false == text.is_empty() ) && ('\"' == text.chars().nth(0).unwrap())
                {
                    result = JsonType::Text( text[1..text.len()-1].to_string() );
                }
                else if "true" == text
                {
                    result = JsonType::Bool( true )
                }
                else if "false" == text
                {
                    result = JsonType::Bool(false )
                }
                else if text.contains( '.' ) 
                {
                    match text.parse::<f32>()
                    {
                        Ok(val) => result = JsonType::Float( val ),
                        Err(_) =>
                        {
                            // ERROR
                            result = JsonType::Null( 0 )
                        }
                    }       
                }
                else
                {
                    match text.parse::<i32>()
                    {
                        Ok(val) => result = JsonType::Integer( val ),
                        Err(_) =>
                        {
                            // ERROR
                            result = JsonType::Null( 0 )
                        }
                    }
                }
            }
            return result;
        }
        else
        {
            JsonType::Null(0)
        }
    }

    fn p_set_data( &mut self, input_key: String, input_data: String )
    {
        let mut data = String::from( "{" );
        if self.is_exist()
        {
            let mut is_first = true;
            let mut is_new_key = true;
            self.file.reset_read_index();
            self.file.open_file();
            loop
            {
                let (key, val) = self.p_get_next_data();
                if 0 == key.len()
                {
                    break;
                }
                else
                {
                    if false == is_first
                    {
                        data.push_str(",");
                    }
                    else
                    {
                        is_first = false;
                    }

                    if input_key == key
                    {
                        data = data + &format!("\"{}\":{}", input_key, input_data );
                        is_new_key = false;
                    }
                    else
                    {
                        data = data + &format!("\"{}\":{}", key, JsonParser::static_jsontype_to_string( &val ) );
                    }
                }
            }

            if true == is_new_key
            {
                if false == is_first
                {
                    data.push_str(",");
                }
                data = data + &format!("\"{}\":{}", input_key, input_data );
            }
            data.push_str("}");
            self.file.close_file();
        }
        else
        {
            data = format!("{{\"{}\":{}}}", input_key, input_data );
        }
        let _ = self.file.write_to_new_file( &data );
    }

    pub fn get_data( &mut self, find_key: String ) -> JsonType
    {
        if self.is_exist()
        {
            if true == find_key.is_empty()
            {
                return self.p_get_next_value();
            }
            self.file.reset_read_index();
            loop
            {
                let key= self.p_get_next_key();
                if 0 == key.len()
                {
                    break;
                }
                else if find_key == key
                {
                    let val = self.p_get_next_value();
                    return val;
                }
                else
                {
                    let _ = self.p_get_next_value();
                }
                
            }
        }
        JsonType::Null(0)
    }

    pub fn set_data( &mut self, key: String, value: &JsonType )
    {
        if true == key.is_empty()
        {
            match value
            {
                JsonType::Object(_) => 
                {
                    let _ = JsonParser::static_jsontype_to_string( value );
                    let _ = self.file.write_to_new_file( &JsonParser::static_jsontype_to_string( value ) );
                },
                _ => {
                    self.p_set_data( String::new(), JsonParser::static_jsontype_to_string( value ) ); // Save as root
                }
                
            };
        }
        else
        {
            self.p_set_data( key, JsonParser::static_jsontype_to_string( value ) );
        }
    }
    
    pub fn static_jsontype_to_string( input: &JsonType ) -> String
    {
        let mut data = String::new();

        match input
        {
            JsonType::Integer(val) => data = format!("{}", val ),
            JsonType::Float(val) => data = format!("{}", val ),
            JsonType::Text(val) => data = format!("\"{}\"", val ),
            JsonType::Bool(val) =>
            {
                if true == *val
                {
                    data = String::from("true");
                }
                else
                {
                    data = String::from("false");
                }
            },
            JsonType::Object(val) =>
            {
                let mut is_first = true;

                data.push_str( "{" );
                for (key,item) in val
                {
                    if false == is_first
                    {
                        data.push_str( "," );
                    }
                    else
                    {
                        is_first = false;
                    }

                    data.push_str( &format!("\"{}\":{}", key, JsonParser::static_jsontype_to_string( item ) ) );
                }
                data.push_str( "}" );
            }
            JsonType::Array(val) =>
            {
                let mut is_first = true;

                data.push_str( "[" );
                for item in val
                {
                    if false == is_first
                    {
                        data.push_str( "," );
                    }
                    else
                    {
                        is_first = false;
                    }

                    data.push_str( &JsonParser::static_jsontype_to_string( &item ) );
                }
                data.push_str( "]" );
            },
            JsonType::Null(_) => data = String::new(),
        }
        return data;
    }

    pub fn delete_data( &mut self, delete_key: String ) -> bool
    {
        if true == delete_key.is_empty()
        {
            self.create_json();
            true
        }
        else
        {
            self.p_delete_data( delete_key )
        }
    }

    fn p_delete_data( &mut self, delete_key: String ) -> bool
    {
        let mut data = String::from( "{" );
        let mut is_delete_success = false;
        if self.is_exist()
        {
            let mut is_first = true;
            self.file.reset_read_index();
            self.file.open_file();
            loop
            {
                let (key, val) = self.p_get_next_data();
                if 0 == key.len()
                {
                    break;
                }
                else
                {
                    if delete_key == key
                    {
                        is_delete_success = true;
                    }
                    else
                    {
                        if false == is_first
                        {
                            data.push_str(",");
                        }
                        else
                        {
                            is_first = false;
                        }
                        data = data + &format!("\"{}\":{}", key, JsonParser::static_jsontype_to_string( &val ) );
                    }
                }
            }
            data.push_str("}");
            self.file.close_file();
        }
        let _ = self.file.write_to_new_file( &data );
        return is_delete_success;
    }
}